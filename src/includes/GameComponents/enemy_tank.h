#ifndef BOT_TANK_H
#define BOT_TANK_H

#include <QTimer>
#include "GameComponents/tank.h"

namespace BattleCity
{
namespace GameComponents
{
/**@class CEnemyTank
Tank object controlled by AI.
*/
class CEnemyTank: public CTank
{
    Q_OBJECT

public:

    CEnemyTank(CDirectionType::EDirection direction, const QPoint& spawnPoint, QObject* parent = nullptr );

    /**@function onHit
    This function is called when an actor collides another actor
    @param[in] hitObject - hit actor.
    */
    virtual void onHit(CActor* hitObject) override;

private slots:

    /**@function moveTimeout
    This function controls tank's moving.
    */
    void moveTimeout();

    /**@function moveTimeout
    This function controls tank's shots.
    */
    void fireTimeout();

private:

    QTimer* m_moveTimer;
    QTimer* m_fireTimer;

    static const int MOVE_DELAY = 20;
    static const int FIRE_DELAY = 1000;
    static const int COUNT_DIRECTIONS = 4;

};

typedef QSharedPointer<CEnemyTank> TEnemyTankShPtr;
typedef QWeakPointer<CEnemyTank> TEnemyTankWkPtr;
}
}
#endif // BOT_TANK_H
