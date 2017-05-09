#ifndef PRE_DEF_MAP_BUILDER_H
#define PRE_DEF_MAP_BUILDER_H

#include <QHash>

#include "map_builder_interface.h"
#include "GameComponents/wall_type.h"
#include "GameComponents/eagle.h"
#include "GameComponents/spawn_actor.h"

namespace BattleCity
{
namespace Map
{
/**@class CPreDefMapBuilder
The class creates map according to internal predefined data.
*/
class CPreDefMapBuilder: public IMapBuilder
{
    typedef QHash<int, GameComponents::CWallType::EWallType> TMapSource;

public:

    /**@function buildMap
    Create map.
    */
    virtual void buildMap(CMap& map) override;

    /**@function getMapDetails
    Return information about created map.
    */
    virtual QSharedPointer<CMapDetails> getMapDetails() override;

    /**@function getEagle
    @return eagle object.
    */
    GameComponents::TEagleWkPtr getEagle() const;

private:

    /**@function createSpawnActor
    Helper. Create spawner.
    */
    GameComponents::TSpawnActorShPtr createSpawnActor(const QPoint& spawnCenter) const;

    /**@function StaticArraySize
    @return array size.
    */
    template<typename T, size_t SZ>
    static size_t StaticArraySize(T(&)[SZ])
    {
        return SZ;
    }

    GameComponents::TEagleWkPtr m_eagle;
    QSharedPointer<CMapDetails> m_mapDetails;

    static TMapSource MakeMap();

    static const TMapSource MAP_SRC;
    static const int MAP_SIZE = 780;
    static const int MAP_SECTION_SIZE = 60;

};
}
}

#endif // PRE_DEF_MAP_BUILDER_H
