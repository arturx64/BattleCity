#ifndef METALL_WALL_H
#define METALL_WALL_H

#include <QRect>

#include "GameComponents/wall_actor.h"

namespace BattleCity
{
namespace GameComponents
{
/**@class CMetallWall
Unbreakable wall object.
*/
class CMetallWall: public CWallActor
{
    Q_OBJECT

public:

    CMetallWall(const QRect& rect, int index, QObject* parent = nullptr);

    /**@function getType
    @return wall type.
    */
    virtual CWallType::EWallType getType() const override;

};

typedef QSharedPointer<CMetallWall> TMetallWallShPtr;
typedef QWeakPointer<CMetallWall> TMetallWallWkPtr;
}
}

#endif // METALL_WALL_H
