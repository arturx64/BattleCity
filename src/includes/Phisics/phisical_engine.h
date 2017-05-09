#ifndef PHISICAL_ENGINE_H
#define PHISICAL_ENGINE_H

#include <QObject>
#include <QMultiHash>
#include <QHash>
#include <QVector>

#include "GameComponents/actor.h"
#include "Phisics/channel.h"
#include "Patterns/singleton.h"
#include "direction.h"

namespace BattleCity
{
namespace Phisics
{
/**@class CPhisicalEngine
Phisical engine.
*/
class CPhisicalEngine : public QObject
{
    Q_OBJECT

    typedef QMultiHash<CChannel::EChannel, GameComponents::TActorWkPtr> TDynamicGroup;
    typedef QHash<int, GameComponents::TActorWkPtr> TStaticGroup;

public:

    CPhisicalEngine(QObject* parent = nullptr);

    /**@function initMap
    Init phisical model of the map.
    */
    void initMap(int mapSize, int mapSections);

    /**@function addStaticObject
    Add static object. The object can't be moved.
    */
    void addStaticObject(GameComponents::TActorShPtr actor);

    /**@function addDynamicObject
    Add dynamic object. The object can be moved.
    */
    void addDynamicObject(GameComponents::TActorShPtr actor);

    /**@function getActorBySectionId
    @return actor according to the map cell id.
    */
    GameComponents::TActorWkPtr getActorBySectionId(int sectionID);

    /**@function getActorBySectionId
    @return map cell id, by object.
    */
    int getSectionIdByActor(GameComponents::TActorShPtr actor);

    /**@function move
    Move object.
    */
    bool move(GameComponents::CActor* actor, CDirectionType::EDirection direct, int steps);

    /**@function isFree
    @return true if actor can be moved.
    */
    bool isFree(GameComponents::CActor* actor);

private:

    /**@function calculateStaticSector
    @return map cell id.
    */
    int calculateStaticSector(GameComponents::CActor* actor) const;

    /**@function calculateStaticSector
    @return map cell id.
    */
    int calculateStaticSector(int coordinate) const;

    /**@function procedStaticCollisionExist
    @return true if the actor doesn't collide any static object.
    */
    bool procedStaticCollisionExist(GameComponents::CActor* actor);

    /**@function procedStaticCollisionExist
    @return true if the actor doesn't collide any dynamic object.
    */
    bool procedDynamicCollisionExist(GameComponents::CActor* actor);

    /**@function deleteDeadDynamicActors
    Remove empty weak references.
    */
    void deleteDeadDynamicActors();

    int m_mapSize;
    int m_mapSections;
    TStaticGroup m_staticObjects;
    TDynamicGroup m_dynamicObjects;
};
}
}

#define PHISICS BattleCity::Patterns::CSingleton<BattleCity::Phisics::CPhisicalEngine>::instance()

#endif // PHISICAL_ENGINE_H
