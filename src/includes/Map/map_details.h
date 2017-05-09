#ifndef MAP_DETAILS_H
#define MAP_DETAILS_H

#include <QObject>
#include <QVector>
#include <QPoint>

#include "GameComponents/spawn_actor.h"

namespace BattleCity
{
namespace Map
{
/**@class CMapDetails
Information about map.
*/
class CMapDetails : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int mapSize READ getMapSize NOTIFY mapSizeChanged)
    Q_PROPERTY(int sectionSize READ getSectionSize NOTIFY sectionSizeChanged)
    Q_PROPERTY(int sectionCount READ getSectionCount NOTIFY sectionCountChanged)

public:

    CMapDetails(QObject* parent = nullptr);
    CMapDetails(const  QList<GameComponents::TSpawnActorShPtr>& enemySpawnPoints,
    GameComponents::TSpawnActorShPtr playerSpawnPoint,
    int mapSize,
    int sectionSize,
    int sectionCount,
    QObject* parent = nullptr);

    QList<GameComponents::TSpawnActorShPtr> getEnemySpawnPoints() const;
    GameComponents::TSpawnActorShPtr getPlayerSpawnPoint() const;
    int getMapSize() const;
    int getSectionSize() const;
    int getSectionCount() const;

signals:

    void mapSizeChanged();
    void sectionSizeChanged();
    void sectionCountChanged();

private:

    QList<GameComponents::TSpawnActorShPtr> m_enemySpawnPoints;
    GameComponents::TSpawnActorShPtr m_playerSpawnPoint;
    int m_mapSize;
    int m_sectionSize;
    int m_sectionCount;
};
}
}

#endif // MAP_DETAILS_H
