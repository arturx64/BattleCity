#include "GameComponents/unit.h"

#include <QQmlComponent>
#include <QQuickWindow>

using namespace BattleCity;
using namespace BattleCity::GameComponents;
using namespace BattleCity::Phisics;

CUnit::CUnit(CDirectionType::EDirection direction, const QPoint& spawnPoint, int unitSize, QObject* parent )
    : CMovableActor(parent)
    , m_direction(direction)
    , m_collider(nullptr)
{
    m_collider = new CRectCollider(this);

    int x = spawnPoint.x() - unitSize / 2;
    int y = spawnPoint.y() - unitSize / 2;

    m_collider->setShiftX(x);
    m_collider->setShiftY(y);
    m_collider->setRect(QRect(0, 0, unitSize, unitSize));

}

CDirectionType::EDirection CUnit::getDirection() const
{
    return m_direction;
}

ICollider* CUnit::getCollider()
{
    return m_collider;
}

void CUnit::updateUI()
{
    QSharedPointer<QQuickItem> item = m_uiItem.toStrongRef();
    if (item)
    {
        item->setX(m_collider->getShiftX());
        item->setY(m_collider->getShiftY());
    }
}

void CUnit::setUiItem(QSharedPointer<QQuickItem> item)
{
    if (item)
    {
        item->setVisible(true);
        item->setWidth(m_collider->getWidth());
        item->setHeight(m_collider->getHeight());
        item->setX(m_collider->getShiftX());
        item->setY(m_collider->getShiftY());
        m_uiItem = item;
    }
}
