#ifndef MOVABLE_ACTOR_H
#define MOVABLE_ACTOR_H

#include "actor.h"
#include "direction.h"

namespace BattleCity
{
namespace GameComponents
{
/**@class CMovableActor
The class gives ability to move object with physics checking.
*/
class CMovableActor: public CActor
{
    Q_OBJECT

public:

    CMovableActor(QObject* parent = nullptr);

protected:

    /**@function updateUI
    Update QML object.
    */
    virtual void updateUI() = 0;

    /**@function move
    Make move with with physics checking.
    @return false if the object can be moved.
    */
    bool move(CDirectionType::EDirection direct, int steps);

};
typedef QSharedPointer<CMovableActor> TMovableActorShPtr;
typedef QWeakPointer<CMovableActor> TMovableActorWkPtr;
}
}

#endif // MOVABLE_ACTOR_H
