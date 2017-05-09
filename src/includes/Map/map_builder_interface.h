#ifndef MAP_BUILDER_INTERFACE_H
#define MAP_BUILDER_INTERFACE_H

#include <QSharedPointer>

#include "map.h"
#include "map_details.h"

namespace BattleCity
{
namespace Map
{
/**@class IMapBuilder
Interface for any type of map builder
*/
class IMapBuilder
{
public:

    /**@function buildMap
    Create map.
    */
    virtual void buildMap(CMap& map) = 0;

    /**@function getMapDetails
    Return information about created map.
    */
    virtual QSharedPointer<CMapDetails> getMapDetails() = 0;

    virtual ~IMapBuilder() = 0 {}
};
}
}

#endif // MAP_BUILDER_INTERFACE_H
