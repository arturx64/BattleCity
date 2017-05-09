#include "GameComponents/tank.h"

using namespace BattleCity;
using namespace BattleCity::GameComponents;

CTank::CTank(CDirectionType::EDirection direction, const QPoint& spawnPoint, QObject* parent )
    : CUnit(direction, spawnPoint, TANK_SIZE, parent)
{
}

void CTank::updateUI()
{
    CUnit::updateUI();
    QSharedPointer<QQuickItem> item = m_uiItem.toStrongRef();
    if (item)
    {
        switch (m_direction)
        {
        case CDirectionType::ED_Up: item->setRotation(0); break;
        case CDirectionType::ED_Right: item->setRotation(90); break;
        case CDirectionType::ED_Left: item->setRotation(-90); break;
        case CDirectionType::ED_Down: item->setRotation(180); break;
        }
    }
}
