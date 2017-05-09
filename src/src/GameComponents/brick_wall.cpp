#include "GameComponents/brick_wall.h"

using namespace BattleCity::GameComponents;
using namespace BattleCity::Phisics;

CBrickWall::CBrickWall(const QRect& rect, int index, QObject* parent)
    : CWallActor(index, parent)
{
    m_collider->setShiftX(rect.x());
    m_collider->setShiftY(rect.y());
    m_collider->setRect(QRect(0, 0, rect.width(), rect.height()), 4);
}

void CBrickWall::applyDamage(int colliderId)
{
    bool remRes = m_collider->removeSubColliderById(colliderId);
    if(remRes && colliderId != -1)
    {
      int val = 1 << colliderId;
      val = ~val;
      m_damageState &= val;
    }
}

void CBrickWall::onHit(CActor* hitObject)
{
    if(hitObject &&
       hitObject->getCollider()->getChannel() == CChannel::eC_EnemyProjectile ||
       hitObject->getCollider()->getChannel() == CChannel::eC_PlayerProjectile)
    {
        int collidedId = m_collider->getLastCollisionId();
        applyDamage(collidedId);
        onUpdate();
    }
}

CWallType::EWallType CBrickWall::getType() const
{
    return CWallType::EWT_Bricks;
}
