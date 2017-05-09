#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Phisics/collider_interface.h"

namespace BattleCity
{
namespace GameComponents
{

/**@class CActor
Main class for any type of game object.
*/
class CActor: public QObject
{
    Q_OBJECT

public:

    CActor(QObject* parent = nullptr);

    /**@function getCollider
    @return object collider.
    */
    virtual Phisics::ICollider* getCollider() = 0;

    /**@function onHit
    This function is called when an actor collides another actor
    @param[in] hitObject - hit actor.
    */
    virtual void onHit(CActor* hitObject) = 0;

    /**@function create
    @return shared pointer ro the actor.
    */
    template<typename Tp, typename... Args>
    static Tp create(Args&&... args)
    {
        return Tp(new Tp::Type(args...), &QObject::deleteLater);
    }

    virtual ~CActor() = 0 {}

signals:

    void hit(CActor* actor);

protected:

    /**@function callHitSignal
    Fire hit signal
    */
    void callHitSignal();

};

typedef QSharedPointer<CActor> TActorShPtr;
typedef QWeakPointer<CActor> TActorWkPtr;
}
}

#endif // ACTOR_H
