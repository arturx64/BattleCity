#include "Map/pre_def_map_builder.h"

#include "GameComponents/spawn_actor.h"
#include "GameComponents/metall_wall.h"
#include "GameComponents/brick_wall.h"
#include "GameComponents/eagle.h"

using namespace BattleCity;
using namespace BattleCity::GameComponents;
using namespace BattleCity::Map;

CPreDefMapBuilder::TMapSource CPreDefMapBuilder::MakeMap()
{
    TMapSource source;
    int brics[] = { 14,  27,  40,  53,  16,  29,  42,  55,  18,  31,  44,  20,  33,  46,
                    22,  35,  48,  61,  24,  37,  50,  63,  80,  81,  70,  72,  87,  88,
                    105, 118, 131, 144, 107, 120, 133, 146, 96,  109, 122, 148, 161, 110,
                    149, 98,  111, 124, 150, 163, 113, 126, 139, 152, 115, 128, 141, 154 };
    for(size_t index = 0; index < StaticArraySize(brics); ++index)
    {
        source.insert(brics[index], CWallType::EWT_Bricks);
    }

    int metall[] = { 78, 32, 90 };
    for(size_t index = 0; index < StaticArraySize(metall); ++index)
    {
        source.insert(metall[index], CWallType::EWT_Metall);
    }

    source.insert(162, CWallType::EWT_Eagle);

    return source;
}

const CPreDefMapBuilder::TMapSource CPreDefMapBuilder::MAP_SRC = MakeMap();

void CPreDefMapBuilder::buildMap(CMap& map)
{
    // Generate map.
    int sectionsCnt = MAP_SIZE / MAP_SECTION_SIZE;

    for(int index = 0; index < sectionsCnt; ++index)
    {
        for(int jndex = 0; jndex < sectionsCnt; ++jndex)
        {
            QRect rect = QRect(jndex * MAP_SECTION_SIZE, index * MAP_SECTION_SIZE, MAP_SECTION_SIZE, MAP_SECTION_SIZE);

            int cellIndex = index * sectionsCnt + jndex;
            CWallType::EWallType cellType = CWallType::EWT_Non;

            if (MAP_SRC.contains(cellIndex))
            {
                cellType = MAP_SRC.value(cellIndex);

            }

            switch(cellType)
            {
            case CWallType::EWT_Bricks:
                map.addWall(CActor::create<TBrickWallShPtr>(rect, map.rowCount()));
                break;
            case CWallType::EWT_Metall:
                map.addWall(CActor::create<TMetallWallShPtr>(rect, map.rowCount()));
                break;
            case CWallType::EWT_Eagle:
            {
                TEagleShPtr eagle = CActor::create<TEagleShPtr>(rect, map.rowCount());
                m_eagle = eagle;
                map.addWall(eagle);
            }
                break;
            default:
                map.addWall(CActor::create<TWallActorShPtr>(map.rowCount()));
            }
        }
    }

    // Fill map data.
    QList<TSpawnActorShPtr> spawns;
    spawns.append(createSpawnActor(QPoint(MAP_SECTION_SIZE / 2, MAP_SECTION_SIZE / 2)));
    spawns.append(createSpawnActor(QPoint(MAP_SIZE - MAP_SECTION_SIZE / 2, MAP_SECTION_SIZE / 2)));
    spawns.append(createSpawnActor(QPoint(MAP_SIZE / 2, MAP_SECTION_SIZE / 2)));
    TSpawnActorShPtr playerSpawn = createSpawnActor(QPoint(MAP_SIZE / 2  - MAP_SECTION_SIZE * 2, MAP_SIZE - MAP_SECTION_SIZE / 2));

    m_mapDetails.reset();
    m_mapDetails = QSharedPointer<CMapDetails>(new CMapDetails(spawns, playerSpawn, MAP_SIZE, MAP_SECTION_SIZE, sectionsCnt));
}

TEagleWkPtr CPreDefMapBuilder::getEagle() const
{
    return m_eagle;
}

TSpawnActorShPtr CPreDefMapBuilder::createSpawnActor(const QPoint& spawnCenter) const
{
    int halfSectionSz = MAP_SECTION_SIZE / 2;
    QRect rc(spawnCenter.x() - halfSectionSz, spawnCenter.y() - halfSectionSz, MAP_SECTION_SIZE, MAP_SECTION_SIZE);
    return CActor::create<TSpawnActorShPtr>(spawnCenter, rc);
}

QSharedPointer<CMapDetails> CPreDefMapBuilder::getMapDetails()
{
    return m_mapDetails;
}
