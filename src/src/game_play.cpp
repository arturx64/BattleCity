#include "game_play.h"

#include <QQmlContext>
#include <QQuickWindow>
#include <QTimer>
#include <QQmlComponent>

#include "Map/pre_def_map_builder.h"
#include "Phisics/phisical_engine.h"
#include "Phisics/channel.h"

using namespace BattleCity;
using namespace BattleCity::GameComponents;
using namespace BattleCity::Map;
using namespace BattleCity::Phisics;

const QString CGamePlay::QML_MAIL_PATH = "qrc:/qml/main.qml";
const QString CGamePlay::MAP_MODEL_NAME = "MapModel";
const QString CGamePlay::MAP_DETAILS_NAME = "MapDetails";
const QString CGamePlay::HEALTH_NAME = "Health";

const QString CGamePlay::DEFEAT_TXT = "Game Over!";
const QString CGamePlay::VICTORY_TXT = "Victory!!!";

const QString CGamePlay::QRC_PROJECTILE = "qrc:/qml/Projectile.qml";
const QString CGamePlay::QRC_ENEMY_TANK = "qrc:/qml/EnemyTank.qml";
const QString CGamePlay::QRC_PLAYER_TANK = "qrc:/qml/PlayerTank.qml";

CGamePlay::CGamePlay(QQmlApplicationEngine* qmlEngine, QObject* parent)
    : QObject(parent)
    , m_qmlEngine(qmlEngine)
    , m_health(nullptr)
{
    m_health = new CGeneralHealth(this);

    initPool();
}

void CGamePlay::initPool()
{
    std::get<ETankPool::eTP_UiTank>(m_player) = createQmlComponent( QRC_PLAYER_TANK );
    std::get<ETankPool::eTP_UiProjectile>(m_player) = createQmlComponent( QRC_PROJECTILE );

    for(size_t index = 0; index < m_enemies.size(); ++index )
    {
        std::get<ETankPool::eTP_UiTank>(m_enemies[index]) = createQmlComponent( QRC_ENEMY_TANK );
        std::get<ETankPool::eTP_UiProjectile>(m_enemies[index]) = createQmlComponent( QRC_PROJECTILE );
    }
}

void CGamePlay::startGame()
{
    // Create map.
    CPreDefMapBuilder mapBuilder;
    mapBuilder.buildMap(m_map);
    m_mapDetails = mapBuilder.getMapDetails();

    QQmlContext* ctx = m_qmlEngine->rootContext();
    if(ctx)
    {
        ctx->setContextProperty(MAP_MODEL_NAME, &m_map);
        ctx->setContextProperty(MAP_DETAILS_NAME, m_mapDetails.data());
        ctx->setContextProperty(HEALTH_NAME, m_health);
    }

    // Assign eagle event death.
    TEagleShPtr eagle = mapBuilder.getEagle().toStrongRef();
    if(eagle)
    {
        connect(eagle.data(), &TEagleShPtr::Type::eagleDestroyed, this, &CGamePlay::eagleDestoyed);
    }

    // Assign map to phisics.
    PHISICS.initMap(m_mapDetails->getMapSize(), m_mapDetails->getSectionCount());
    auto& mapData = m_map.getDataRef();
    for(int index = 0; index <  mapData.length(); ++index)
    {
        if(mapData[index]->getType() != CWallType::EWT_Non)
        {
            PHISICS.addStaticObject(mapData[index]);
        }
    }

    spawnPlayer();
    spawnEnemy();
    spawnEnemy();
    spawnEnemy();
}

void CGamePlay::eagleDestoyed()
{
    finishGame(DEFEAT_TXT);
}

void CGamePlay::playerDestoyed(GameComponents::CActor*)
{
    std::get<ETankPool::eTP_Tank>(m_player).reset();
    if(isDefeat())
    {
        finishGame(DEFEAT_TXT);
    }
    else
    {
        spawnPlayer();
    }
}

void CGamePlay::enemyPlayerDestroyed(CActor* actor)
{
    for(size_t index = 0; index < m_enemies.size(); ++index)
    {
        if( std::get<ETankPool::eTP_Tank>(m_enemies[index]) == actor)
        {
            std::get<ETankPool::eTP_Tank>(m_enemies[index]).reset();
            break;
        }
    }

    if(isVictory())
    {
        finishGame(VICTORY_TXT);
    }
    else
    {
        spawnEnemy();
    }
}

void CGamePlay::enemyProjectileDestroyed(GameComponents::CActor* actor)
{
    for(size_t index = 0; index < m_enemies.size(); ++index)
    {
        if( std::get<ETankPool::eTP_Projectile>(m_enemies[index]) == actor)
        {
            std::get<ETankPool::eTP_Projectile>(m_enemies[index]).reset();
            break;
        }
    }
}

void CGamePlay::spawnEnemyProjectile(CDirectionType::EDirection direct, const QPoint& spawnPoint, CActor* owner)
{
    for(size_t index = 0; index < m_enemies.size(); ++index)
    {
        if(!std::get<ETankPool::eTP_Projectile>(m_enemies[index]) &&
                std::get<ETankPool::eTP_Tank>(m_enemies[index]) == owner)
        {
            TProjectileActorShPtr enemyProj = CActor::create<TProjectileActorShPtr>(CChannel::EChannel::eC_EnemyProjectile, direct, spawnPoint);
            enemyProj->getCollider()->setCollisionChannels({CChannel::eC_Wall, CChannel::eC_PlayerTank});
            connect(enemyProj.data(), &TProjectileActorShPtr::Type::hit, this, &CGamePlay::enemyProjectileDestroyed);
            PHISICS.addDynamicObject(enemyProj);

            enemyProj->setUiItem(std::get<ETankPool::eTP_UiProjectile>(m_enemies[index]));
            std::get<ETankPool::eTP_Projectile>(m_enemies[index]) = enemyProj;
            break;
        }
    }
}

void CGamePlay::spawnPlayerProjectile(CDirectionType::EDirection direct, const QPoint& spawnPoint, CActor*)
{
    if(!std::get<ETankPool::eTP_Projectile>(m_player) )
    {
        TProjectileActorShPtr playerProjectile = CActor::create<TProjectileActorShPtr>(CChannel::EChannel::eC_PlayerProjectile, direct, spawnPoint);
        playerProjectile->getCollider()->setCollisionChannels({CChannel::eC_Wall, CChannel::eC_EnemyTank});
        connect(playerProjectile.data(), &TProjectileActorShPtr::Type::hit, this, &CGamePlay::playerProjectileDestoyed);
        PHISICS.addDynamicObject(playerProjectile);

        playerProjectile->setUiItem(std::get<ETankPool::eTP_UiProjectile>(m_player));
        std::get<ETankPool::eTP_Projectile>(m_player) = playerProjectile;
    }
}

void CGamePlay::playerProjectileDestoyed(GameComponents::CActor*)
{
    std::get<ETankPool::eTP_Projectile>(m_player).reset();
}

void CGamePlay::spawnPlayer()
{
    TSpawnActorShPtr spawnActor = m_mapDetails->getPlayerSpawnPoint();
    QPoint spawnPoint = spawnActor->getSpawnPosition();
    TPlayerTankShPtr player = spawnActor->spawn<TPlayerTankShPtr>(CDirectionType::ED_Up, m_qmlEngine, spawnPoint);
    if(player)
    {
        connect(player.data(), &TTankShPtr::Type::fired, this, &CGamePlay::spawnPlayerProjectile);
        connect(player.data(), &TTankShPtr::Type::hit, this, &CGamePlay::playerDestoyed);
        PHISICS.addDynamicObject(player);

        player->setUiItem(std::get<ETankPool::eTP_UiTank>(m_player));
        std::get<ETankPool::eTP_Tank>(m_player) = player;
        m_health->killPlayer();
    }
    else
    {
        QTimer::singleShot(SPAWN_DELAY, this, &CGamePlay::spawnPlayer);
    }
}

bool CGamePlay::spawnSingleEnemy(TankPool& tankPool)
{
    auto spawnActors = m_mapDetails->getEnemySpawnPoints();

    QVector<int> randIdxes (spawnActors.size());
    int stepper = 0;
    std::generate(randIdxes.begin(), randIdxes.end(), [&](){ return stepper++;});
    std::random_shuffle (randIdxes.begin(), randIdxes.end() );

    for(int spawnActorIndex = 0; spawnActorIndex < randIdxes.size(); ++spawnActorIndex)
    {
        int idx = randIdxes[spawnActorIndex];
        auto spawnActor = spawnActors[idx];
        QPoint spawnPoint = spawnActor->getSpawnPosition();
        TEnemyTankShPtr enemy = spawnActor->spawn<TEnemyTankShPtr>(CDirectionType::ED_Down, spawnPoint);
        if(enemy)
        {
            connect(enemy.data(), &TProjectileActorShPtr::Type::hit, this, &CGamePlay::enemyPlayerDestroyed);
            connect(enemy.data(), &TTankShPtr::Type::fired, this, &CGamePlay::spawnEnemyProjectile);
            PHISICS.addDynamicObject(enemy);

            enemy->setUiItem(std::get<ETankPool::eTP_UiTank>(tankPool));
            std::get<ETankPool::eTP_Tank>(tankPool) = enemy;
            m_health->killEnemy();
            return true;
        }
    }
    return false;
}

void CGamePlay::spawnEnemy()
{
    if(!m_health->getEnemyHealth())
        return;

    for(size_t index = 0; index < m_enemies.size(); ++index)
    {
        if(!std::get<ETankPool::eTP_Tank>(m_enemies[index]) &&
                !std::get<ETankPool::eTP_Projectile>(m_enemies[index]))
        {
            if(spawnSingleEnemy(m_enemies[index]))
                return;
        }
    }
    QTimer::singleShot(SPAWN_DELAY, this, &CGamePlay::spawnEnemy);
}

bool CGamePlay::isEnemyOnTheMap() const
{
    for(size_t index = 0; index < m_enemies.size(); ++index)
    {
        if( std::get<ETankPool::eTP_Tank>(m_enemies[index]))
        {
            return true;
        }
    }
    return false;
}

bool CGamePlay::isVictory() const
{
    return !m_health->getEnemyHealth() && !isEnemyOnTheMap();
}

bool CGamePlay::isDefeat() const
{
    return !m_health->getPlayerHealth() && !std::get<ETankPool::eTP_Tank>(m_player);
}

void CGamePlay::killPoolItem(TankPool& tankPool)
{
    std::get<ETankPool::eTP_Tank>(tankPool).reset();
    std::get<ETankPool::eTP_Projectile>(tankPool).reset();
    std::get<ETankPool::eTP_UiProjectile>(tankPool).reset();
    std::get<ETankPool::eTP_UiTank>(tankPool).reset();
}

void CGamePlay::finishGame(const QString& finishMessage)
{
    // Kill all partisipants.
    for(size_t index = 0; index < m_enemies.size(); ++index)
    {
        killPoolItem(m_enemies[index]);
    }
    killPoolItem(m_player);

    // Show message.
    QObject* root = m_qmlEngine->rootObjects().first();
    if(root)
    {
        QObject *item = root->findChild<QObject*>("gamePageObject");
        if(item)
        {
            QMetaObject::invokeMethod(item, "showEndSceen",  Q_ARG(QVariant, finishMessage));
        }
    }

    // Restart game.
    QTimer::singleShot(RESTART_DELAY, this, &CGamePlay::restart);
}

CGamePlay::TQuickItemShPtr CGamePlay::createQmlComponent(const QString& qmlPath)
{
    QQmlComponent component(m_qmlEngine, QUrl(qmlPath));
    QObject* qmlObj = component.create();
    if (!qmlObj)
    {
        qFatal("Can't create QML tank component.");
        return TQuickItemShPtr();
    }

    QQuickItem* item = qobject_cast<QQuickItem*>(qmlObj);
    if (!item)
    {
        qFatal("Can't get quick item from QML component.");
        return TQuickItemShPtr();
    }

    TQuickItemShPtr itemSh = TQuickItemShPtr(item, &QObject::deleteLater);
    QQmlEngine::setObjectOwnership(itemSh.data(), QQmlEngine::CppOwnership);

    QQuickWindow *window = qobject_cast<QQuickWindow*>(m_qmlEngine->rootObjects().at(0));
    if (!window)
    {
        qFatal("Can't get window from QML.");
        return TQuickItemShPtr();
    }
    itemSh->setParentItem(window->contentItem());
    return itemSh;
}
