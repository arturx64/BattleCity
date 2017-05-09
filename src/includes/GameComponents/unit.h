#ifndef UNIT_H
#define UNIT_H

#include <QQuickItem>
#include <QPoint>

#include "GameComponents/movable_actor.h"
#include "Phisics/rect_collider.h"
#include "direction.h"

namespace BattleCity
{
namespace GameComponents
{
/**@class CUnit
Unit object. Base class for any unit.
*/
class CUnit: public CMovableActor
{
    Q_OBJECT

public:

    CUnit(CDirectionType::EDirection direction, const QPoint& spawnPoint, int unitSize, QObject* parent = nullptr);

    /**@function getCollider
    @return object collider.
    */
    virtual Phisics::ICollider* getCollider() override;

    /**@function getDirection
    @return object direction.
    */
    CDirectionType::EDirection getDirection() const;

    /**@function setUiItem
    Attach QML object.
    */
    void setUiItem(QSharedPointer<QQuickItem> item);

protected:

    /**@function updateUI
    Update QML object.
    */
    virtual void updateUI() override;

    QWeakPointer<QQuickItem>  m_uiItem;
    CDirectionType::EDirection m_direction;
    Phisics::CRectCollider* m_collider;

};
}
}

#endif // UNIT_H
