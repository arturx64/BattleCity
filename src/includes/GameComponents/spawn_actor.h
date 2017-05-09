#ifndef SPAWN_ACTOR_H
#define SPAWN_ACTOR_H

#include <QObject>
#include <QRect>
#include <QPoint>
#include <QWeakPointer>

#include "GameComponents/actor.h"
#include "Phisics/phisical_engine.h"
#include "Phisics/rect_collider.h"

namespace BattleCity
{
namespace GameComponents
{
/**@class CSpawnActor
Actor spawner.
*/
class CSpawnActor: public CActor
{
    Q_OBJECT

public:

    CSpawnActor(const QPoint& spawnPos, const QRect& actorSize, QObject* parent = nullptr);

    /**@function getSpawnPosition
    @return center of the spawn point.
    */
    QPoint getSpawnPosition() const;

    /**@function onHit
    This function is called when an actor collides another actor
    @param[in] hitObject - hit actor.
    */
    virtual void onHit(CActor* hitObject) override;

    /**@function getCollider
    @return object collider.
    */
    virtual Phisics::ICollider* getCollider() override;

    /**@function spawn
    Create actor according to the spawn position.
    @return false if the object can't be spawned.
    */
    template<typename Tp, typename... Args>
    Tp spawn(Args&&... args)
    {
        if(isFreeForSpawn())
        {
            return CActor::create<Tp>(args...);
        }
        return Tp();
    }

private:

    /**@function isFreeForSpawn
    @return true if spawn area is clear(without tanks, walls, bullets etc.).
    */
    bool isFreeForSpawn();

    QPoint m_spawnPoint;
    Phisics::CRectCollider* m_collider;
};

typedef QSharedPointer<CSpawnActor> TSpawnActorShPtr;
typedef QWeakPointer<CSpawnActor> TSpawnActorWkPtr;
}
}


#endif // SPAWN_ACTOR_H
