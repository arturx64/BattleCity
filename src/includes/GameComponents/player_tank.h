#ifndef PLAYER_TANK_H
#define PLAYER_TANK_H

#include <QList>
#include <QTimer>
#include "GameComponents/tank.h"

namespace BattleCity
{
namespace GameComponents
{
/**@class CPlayerTank
Tank object controlled by Player.
*/
class CPlayerTank: public CTank
{
    Q_OBJECT

public:

    CPlayerTank(CDirectionType::EDirection direction, QQmlApplicationEngine* engine, const QPoint& spawnPoint, QObject* parent = nullptr );

    /**@function onHit
    This function is called when an actor collides another actor
    @param[in] hitObject - hit actor.
    */
    virtual void onHit(CActor* hitObject) override;

protected:

    /**@function eventFilter
    Get information about pushed buttons.
    */
    bool eventFilter(QObject* obj, QEvent* event);

private slots:

    /**@function updateStep
    Make move.
    */
    void updateStep();

private:

    /**@function removeMovement
    Delete direction from the controller collection.
    */
    void removeMovement(CDirectionType::EDirection direction);

    QTimer* m_timer;
    QList<CDirectionType::EDirection> moveDirection;

    static const int MOVE_DELAY = 20;
};

typedef QSharedPointer<CPlayerTank> TPlayerTankShPtr;
typedef QWeakPointer<CPlayerTank> TPlayerTankWkPtr;
}
}

#endif // PLAYER_TANK_H
