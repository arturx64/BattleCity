#ifndef GAME_PLAY_H
#define GAME_PLAY_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QString>
#include <QQuickItem>
#include <array>
#include <tuple>

#include "Map/map.h"
#include "Map/map_details.h"
#include "GameComponents/player_tank.h"
#include "GameComponents/enemy_tank.h"
#include "GameComponents/projectile_actor.h"
#include "direction.h"
#include "general_health.h"

namespace BattleCity
{
class CGamePlay : public QObject
{
    Q_OBJECT

    typedef QSharedPointer<QQuickItem> TQuickItemShPtr;
    typedef std::tuple<GameComponents::TTankShPtr, GameComponents::TProjectileActorShPtr, TQuickItemShPtr, TQuickItemShPtr> TankPool;
    enum ETankPool
    {
        eTP_Tank,
        eTP_Projectile,
        eTP_UiTank,
        eTP_UiProjectile,
    };

    typedef std::array<TankPool, 3> TEnemyTankGroup;

public:

    CGamePlay(QQmlApplicationEngine* qmlEngine, QObject* parent = nullptr);
    void startGame();

signals:

    void restart();
    void enemyHealthChanged();
    void playerHealthChanged();

private slots:

    void spawnPlayerProjectile(CDirectionType::EDirection direct, const QPoint& spawnPoint, GameComponents::CActor* owner);
    void spawnEnemyProjectile(CDirectionType::EDirection direct, const QPoint& spawnPoint, GameComponents::CActor* owner);
    void spawnPlayer();
    void spawnEnemy();
    void enemyPlayerDestroyed(GameComponents::CActor* actor);
    void enemyProjectileDestroyed(GameComponents::CActor* actor);
    void playerDestoyed(GameComponents::CActor* actor);
    void playerProjectileDestoyed(GameComponents::CActor* actor);
    void eagleDestoyed();

private:

    void initPool();
    bool isVictory() const;
    bool isDefeat() const;
    bool isEnemyOnTheMap() const;
    void finishGame(const QString& finishMessage);
    bool spawnSingleEnemy(TankPool& tankPool);
    void killPoolItem(TankPool& tankPool);
    TQuickItemShPtr createQmlComponent(const QString& qmlPath);

    QQmlApplicationEngine* m_qmlEngine;
    Map::CMap m_map;
    QSharedPointer<Map::CMapDetails> m_mapDetails;
    CGeneralHealth* m_health;

    TankPool m_player;
    TEnemyTankGroup m_enemies;

    static const int RESTART_DELAY = 5000;
    static const int SPAWN_DELAY = 1000;

    static const QString QML_MAIL_PATH;
    static const QString MAP_MODEL_NAME;
    static const QString MAP_DETAILS_NAME;
    static const QString HEALTH_NAME;

    static const QString DEFEAT_TXT;
    static const QString VICTORY_TXT;

    static const QString QRC_PROJECTILE;
    static const QString QRC_ENEMY_TANK;
    static const QString QRC_PLAYER_TANK;
};
}

#endif // GAME_PLAY_H
