#ifndef BRICKS_WALL_H
#define BRICKS_WALL_H

#include <QRect>

#include "GameComponents/wall_actor.h"

namespace BattleCity
{
namespace GameComponents
{
/**@class CBrickWall
Destructible wall object
*/
class CBrickWall: public CWallActor
{
    Q_OBJECT

public:

    CBrickWall(const QRect& rect, int index, QObject* parent = nullptr);

    /**@function onHit
    This function is called when an actor collides another actor
    @param[in] hitObject - hit actor.
    */
    virtual void onHit(CActor* hitObject) override;

    /**@function getType
    @return wall type.
    */
    virtual CWallType::EWallType getType() const override;

private:

    /**@function applyDamage
    Notify UI about damaged wall.
    */
    void applyDamage(int colliderId);

};

typedef QSharedPointer<CBrickWall> TBrickWallShPtr;
typedef QWeakPointer<CBrickWall> TBrickWallWkPtr;
}
}

#endif // BRICKS_WALL_H
