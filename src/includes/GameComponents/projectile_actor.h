#ifndef PROJECTILE_ACTOR_H
#define PROJECTILE_ACTOR_H

#include <QTimer>

#include "GameComponents/unit.h"
#include "Phisics/channel.h"

namespace BattleCity
{
namespace GameComponents
{
/**@class CProjectileActor
Projectile object.
*/
class CProjectileActor: public CUnit
{
    Q_OBJECT

public:

    CProjectileActor(Phisics::CChannel::EChannel targetChannel, CDirectionType::EDirection direction, const QPoint& spawnPoint, QObject* parent = nullptr );

    /**@function onHit
    This function is called when an actor collides another actor
    @param[in] hitObject - hit actor.
    */
    virtual void onHit(CActor* hitObject) override;

private slots:

    /**@function updateStep
    Make move.
    */
    void updateStep();

private:

    QTimer* m_timer;

    static const int PROJECTILE_SIZE = 17;

    static const int MOVE_DELAY = 10;
};

typedef QSharedPointer<CProjectileActor> TProjectileActorShPtr;
typedef QWeakPointer<CProjectileActor> TProjectileActorWkPtr;
}
}

#endif // PROJECTILE_ACTOR_H
