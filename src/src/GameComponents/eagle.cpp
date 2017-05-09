#include "GameComponents/eagle.h"

using namespace BattleCity::GameComponents;
using namespace BattleCity::Phisics;

CEagle::CEagle(const QRect& rect, int index, QObject* parent)
    : CWallActor(index, parent)
{
    m_collider->setShiftX(rect.x());
    m_collider->setShiftY(rect.y());
    m_collider->setRect(QRect(0, 0, rect.width(), rect.height()), 1);
}

void CEagle::onHit(CActor* hitObject)
{
    if(hitObject &&
       hitObject->getCollider()->getChannel() == CChannel::eC_EnemyProjectile ||
       hitObject->getCollider()->getChannel() == CChannel::eC_PlayerProjectile)
    {
        m_damageState = 0;
        onUpdate();
        emit eagleDestroyed();
    }
}

CWallType::EWallType CEagle::getType() const
{
    return CWallType::EWT_Eagle;
}
