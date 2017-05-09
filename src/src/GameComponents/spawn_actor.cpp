#include "GameComponents/spawn_actor.h"

using namespace BattleCity::GameComponents;
using namespace BattleCity::Phisics;

CSpawnActor::CSpawnActor(const QPoint& spawnPos, const QRect& actorSize, QObject* parent)
    : CActor(parent)
    , m_spawnPoint(spawnPos)
    , m_collider(nullptr)
{
    m_collider = new CRectCollider(this);

    m_collider->setChannel(CChannel::eC_Spawn);
    m_collider->setCollisionChannels({
                                        CChannel::eC_Wall,
                                        CChannel::eC_EnemyProjectile,
                                        CChannel::eC_EnemyTank,
                                        CChannel::eC_PlayerProjectile,
                                        CChannel::eC_PlayerTank});

    m_collider->setShiftX(actorSize.x());
    m_collider->setShiftY(actorSize.y());
    m_collider->setRect(QRect(0, 0, actorSize.width(), actorSize.height()));
}

QPoint CSpawnActor::getSpawnPosition() const
{
    return m_spawnPoint;
}

ICollider* CSpawnActor::getCollider()
{
    return m_collider;
}

void CSpawnActor::onHit(CActor*)
{
    // Ignore hit.
}

bool CSpawnActor::isFreeForSpawn()
{
    return PHISICS.isFree(this);
}
