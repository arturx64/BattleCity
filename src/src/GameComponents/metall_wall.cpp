#include "GameComponents/metall_wall.h"

using namespace BattleCity;
using namespace BattleCity::GameComponents;
using namespace BattleCity::Phisics;

CMetallWall::CMetallWall(const QRect& rect, int index, QObject* parent)
    : CWallActor(index, parent)
{
    m_collider->setShiftX(rect.x());
    m_collider->setShiftY(rect.y());
    m_collider->setRect(QRect(0, 0, rect.width(), rect.height()), 1);
}

CWallType::EWallType CMetallWall::getType() const
{
    return CWallType::EWT_Metall;
}
