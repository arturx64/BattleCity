#include "GameComponents/wall_actor.h"

using namespace BattleCity::GameComponents;
using namespace BattleCity::Phisics;

CWallActor::CWallActor(int index, QObject* parent)
    : CActor(parent)
    , m_damageState(FULL_HEALTH)
    , m_collider(nullptr)
    , m_index(index)
{
    m_collider = new CTabularCollider(this);
    m_collider->setChannel(Phisics::CChannel::eC_Wall);
}

void CWallActor::onHit(CActor*)
{
    // ignore any hit.
}

void CWallActor::onUpdate()
{
    emit updated(m_index);
}

int CWallActor::getDamage() const
{
    return m_damageState;
}

ICollider* CWallActor::getCollider()
{
    return m_collider;
}

CWallType::EWallType CWallActor::getType() const
{
    return CWallType::EWT_Non;
}

