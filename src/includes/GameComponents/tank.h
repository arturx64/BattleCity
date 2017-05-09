#ifndef TANK_H
#define TANK_H

#include <QQmlApplicationEngine>
#include <QQuickItem>

#include "GameComponents/unit.h"
#include "direction.h"

namespace BattleCity
{
namespace GameComponents
{
/**@class CTank
Tank object
*/
class CTank: public CUnit
{
    Q_OBJECT
public:

    CTank(CDirectionType::EDirection direction, const QPoint& spawnPoint, QObject* parent = nullptr );

signals:

    void fired(CDirectionType::EDirection direction, const QPoint& spawnPoint, CActor* owner);

protected:

    /**@function updateUI
    Update QML object.
    */
    virtual void updateUI() override;

    static const int TANK_SPEED = 5;

private:

    static const int TANK_SIZE = 30;
};

typedef QSharedPointer<CTank> TTankShPtr;
typedef QWeakPointer<CTank> TTankWkPtr;
}
}

#endif // TANK_H
