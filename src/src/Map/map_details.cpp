#include "Map/map_details.h"

using namespace BattleCity::Map;
using namespace BattleCity::GameComponents;

CMapDetails::CMapDetails(QObject* parent)
    : QObject(parent)
    , m_mapSize(0)
    , m_sectionSize(0)
    , m_sectionCount(0)
{
}

CMapDetails::CMapDetails(const QList<TSpawnActorShPtr>& enemySpawnPoints,
                         TSpawnActorShPtr playerSpawnPoint,
                         int mapSize,
                         int sectionSize,
                         int sectionCount,
                         QObject* parent)
    : QObject(parent)
    , m_enemySpawnPoints(enemySpawnPoints)
    , m_playerSpawnPoint(playerSpawnPoint)
    , m_mapSize(mapSize)
    , m_sectionSize(sectionSize)
    , m_sectionCount(sectionCount)
{
}

QList<TSpawnActorShPtr> CMapDetails::getEnemySpawnPoints() const
{
    return m_enemySpawnPoints;
}

TSpawnActorShPtr CMapDetails::getPlayerSpawnPoint() const
{
    return m_playerSpawnPoint;
}

int CMapDetails::getMapSize() const
{
    return m_mapSize;
}

int CMapDetails::getSectionSize() const
{
    return m_sectionSize;
}

int CMapDetails::getSectionCount() const
{
    return m_sectionCount;
}
