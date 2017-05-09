#include "GameComponents/enemy_tank.h"

#include <QtGlobal>

using namespace BattleCity;
using namespace BattleCity::GameComponents;
using namespace BattleCity::Phisics;

CEnemyTank::CEnemyTank(CDirectionType::EDirection direction, const QPoint& spawnPoint, QObject* parent )
    : CTank(direction, spawnPoint, parent)
    , m_moveTimer(nullptr)
    , m_fireTimer(nullptr)
{
    m_collider->setChannel(CChannel::eC_EnemyTank);
    m_collider->setCollisionChannels({CChannel::eC_Wall, CChannel::eC_EnemyTank, CChannel::eC_PlayerTank});

    m_moveTimer = new QTimer(this);
    connect(m_moveTimer, &QTimer::timeout, this, &CEnemyTank::moveTimeout);
    m_moveTimer->start(MOVE_DELAY);
    m_fireTimer = new QTimer(this);
    connect(m_fireTimer, &QTimer::timeout, this, &CEnemyTank::fireTimeout);
    m_fireTimer->start(FIRE_DELAY);
}

void CEnemyTank::onHit(CActor* hitObject)
{
    if(hitObject && hitObject->getCollider()->getChannel() == CChannel::eC_PlayerProjectile)
    {
        QSharedPointer<QQuickItem> item = m_uiItem.toStrongRef();
        if (item)
        {
            item->setVisible(false);
        }
        callHitSignal();
    }
}

void CEnemyTank::fireTimeout()
{
    int x = m_collider->getShiftX() + m_collider->getWidth() / 2;
    int y = m_collider->getShiftY() + m_collider->getHeight() / 2;
    emit fired(m_direction, QPoint(x, y), this);
}

void CEnemyTank::moveTimeout()
{
    bool res = move(m_direction, TANK_SPEED);

    if(!res)
    {
        int randDir = qrand() % COUNT_DIRECTIONS;

        CDirectionType::EDirection newDirect = static_cast<CDirectionType::EDirection>(randDir);
        m_direction = newDirect;
    }
}
