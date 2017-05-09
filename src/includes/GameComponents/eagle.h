#ifndef EAGLE_H
#define EAGLE_H
#include <QRect>

#include "GameComponents/wall_actor.h"

namespace BattleCity
{
namespace GameComponents
{
/**@class CEagle
Destructible eagle object. This object must be destroyed for defeat.
*/
class CEagle: public CWallActor
{
    Q_OBJECT

public:

    CEagle(const QRect& rect, int index, QObject* parent = nullptr);

    /**@function onHit
    This function is called when an actor collides another actor
    @param[in] hitObject - hit actor.
    */
    virtual void onHit(CActor* hitObject) override;

    /**@function getType
    @return wall type.
    */
    virtual CWallType::EWallType getType() const override;

signals:

    void eagleDestroyed();

};

typedef QSharedPointer<CEagle> TEagleShPtr;
typedef QWeakPointer<CEagle> TEagleWkPtr;
}
}

#endif // EAGLE_H
