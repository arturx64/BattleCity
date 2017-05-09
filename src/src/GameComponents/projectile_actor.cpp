#include "GameComponents/projectile_actor.h"

using namespace BattleCity;
using namespace BattleCity::GameComponents;
using namespace BattleCity::Phisics;

CProjectileActor::CProjectileActor(CChannel::EChannel targetChannel, CDirectionType::EDirection direction, const QPoint& spawnPoint, QObject* parent )
    : CUnit(direction, spawnPoint, PROJECTILE_SIZE, parent)
{
    m_collider->setChannel(targetChannel);
    m_collider->setCollisionChannels({CChannel::eC_Wall});

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CProjectileActor::updateStep);
    m_timer->start(MOVE_DELAY);
}

void CProjectileActor::onHit(CActor*)
{
    QSharedPointer<QQuickItem> item = m_uiItem.toStrongRef();
    if (item)
    {
        item->setVisible(false);
    }
    callHitSignal();
}

void CProjectileActor::updateStep()
{
    move(m_direction, 5);
}

