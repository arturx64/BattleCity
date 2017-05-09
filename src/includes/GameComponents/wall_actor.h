#ifndef WALL_ACTOR_H
#define WALL_ACTOR_H

#include "actor.h"
#include "wall_type.h"
#include "Phisics/tabular_collider.h"

namespace BattleCity
{
namespace GameComponents
{
/**@class CWallActor
Base class for all walls.
*/
class CWallActor: public CActor
{
    Q_OBJECT

public:

    CWallActor(int index, QObject* parent = nullptr);

    /**@function getDamage
    @return damage info.
    */
    int getDamage() const;

    /**@function getCollider
    @return object collider.
    */
    virtual Phisics::ICollider* getCollider() override;

    /**@function onHit
    This function is called when an actor collides another actor
    @param[in] hitObject - hit actor.
    */
    virtual void onHit(CActor* hitObject) override;

    /**@function getType
    @return wall type.
    */
    virtual CWallType::EWallType getType() const;

signals:

    void updated(int indexVal);

protected:

    /**@function onUpdate
    update QML model.
    */
    void onUpdate();

    int m_damageState;   
    Phisics::CTabularCollider* m_collider;

private:

    int m_index;

    static const int FULL_HEALTH = 0x0000FFFF;

};

typedef QSharedPointer<CWallActor> TWallActorShPtr;
typedef QWeakPointer<CWallActor> TWallActorWkPtr;
}
}

#endif // WALL_ACTOR_H
