#include "Phisics/phisical_engine.h"

using namespace BattleCity;
using namespace BattleCity::Phisics;
using namespace BattleCity::GameComponents;

CPhisicalEngine::CPhisicalEngine(QObject* parent)
    : QObject(parent)
    , m_mapSize( 0 )
    , m_mapSections( 0 )
{
}

void CPhisicalEngine::initMap(int mapSize, int mapSections)
{
    m_staticObjects.clear();
    m_dynamicObjects.clear();
    m_mapSize = mapSize;
    m_mapSections = mapSections;
}

TActorWkPtr CPhisicalEngine::getActorBySectionId(int sectionID)
{
    return m_staticObjects.value(sectionID, TActorWkPtr());
}

void CPhisicalEngine::addStaticObject(TActorShPtr actor)
{
    m_staticObjects.insert(calculateStaticSector(actor.data()), actor);
}

void CPhisicalEngine::addDynamicObject(TActorShPtr actor)
{
    deleteDeadDynamicActors();
    m_dynamicObjects.insert(actor->getCollider()->getChannel(), actor);
}

int CPhisicalEngine::getSectionIdByActor(TActorShPtr actor)
{
    return calculateStaticSector(actor.data());
}

int CPhisicalEngine::calculateStaticSector(int coordinate) const
{
    if (coordinate > m_mapSize)
        return - 1;

    if (coordinate >= m_mapSize - 1)
        return m_mapSections - 1;

    double cellRatio = static_cast<double>(coordinate) / (m_mapSize - 1 );

    int cell = cellRatio * m_mapSections;

    int sectionSz = m_mapSize / m_mapSections;

    // Correction because of possible fаloating point inaccurancy.
    for( int index = - 1; index < 2; ++index )
    {
        int testIdx = cell + index;
        if(testIdx >= 0 && testIdx < m_mapSections)
        {
            int sectionStartPos = testIdx * sectionSz;
            if(coordinate >= sectionStartPos && coordinate < (sectionStartPos + sectionSz))
            {
                return testIdx;
            }
        }
    }

    return -1;
}

int CPhisicalEngine::calculateStaticSector(CActor* actor) const
{
    int cellX = calculateStaticSector(actor->getCollider()->getShiftX());
    int cellY = calculateStaticSector(actor->getCollider()->getShiftY());

    if(cellX != -1 && cellY != -1)
    {
        return cellY * m_mapSections + cellX;
    }

    return -1;
}

bool CPhisicalEngine::procedStaticCollisionExist(CActor* actor)
{
    int x = actor->getCollider()->getShiftX();
    int y = actor->getCollider()->getShiftY();
    int width = actor->getCollider()->getWidth();
    int height = actor->getCollider()->getHeight();

    bool hitRes = false;
    for(int index = 0; index <= 1; ++index)
        for(int jndex = 0; jndex <= 1; ++jndex)
        {
            // Check static objects.
            int staticObjectXCell = calculateStaticSector(x + (index * width) );
            int staticObjectYCell = calculateStaticSector(y + (jndex * height) );

            // Check border.
            if(staticObjectXCell == -1 || staticObjectYCell == - 1)
            {
                actor->onHit(nullptr);
                return true;
            }

            // Check static collision.
            int newCell = staticObjectYCell * m_mapSections + staticObjectXCell;
            if( m_staticObjects.contains(newCell))
            {         
                TActorWkPtr statObjWk = m_staticObjects.value(newCell);
                TActorShPtr statObjSh = statObjWk.toStrongRef();

                CChannel channelCollision = actor->getCollider()->getCollisionChannels();

                if(statObjSh &&
                   channelCollision.isFlag(statObjSh->getCollider()->getChannel()) &&
                   actor->getCollider()->isCollide(statObjSh->getCollider()))
                {
                    actor->onHit(statObjSh.data());
                    statObjSh->onHit(actor);
                    hitRes = true;
                }
            }
        }
    return hitRes;
}

bool CPhisicalEngine::procedDynamicCollisionExist(GameComponents::CActor* actor)
{
    bool hitRes = false;
    CChannel channelCollision = actor->getCollider()->getCollisionChannels();
    QVector<CChannel::EChannel> collisionChannels = channelCollision.getFlags();

    for(auto channel: collisionChannels)
    {
        QList<TDynamicGroup::mapped_type> potentialHitTargets = m_dynamicObjects.values(channel);
        for(auto potentialHitTarget: potentialHitTargets)
        {
            TActorShPtr dynamictObjSh = potentialHitTarget.toStrongRef();
            if(dynamictObjSh &&
               dynamictObjSh != actor &&
               actor->getCollider()->isCollide(dynamictObjSh->getCollider()))
            {
                actor->onHit(dynamictObjSh.data());
                dynamictObjSh->onHit(actor);
                hitRes = true;
            }
        }
    }
    return hitRes;
}

void CPhisicalEngine::deleteDeadDynamicActors()
{
    TDynamicGroup::iterator iter = m_dynamicObjects.begin();
    while(iter != m_dynamicObjects.end())
    {
        if(!iter.value())
        {
            iter = m_dynamicObjects.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

bool CPhisicalEngine::isFree(GameComponents::CActor* actor)
{
    return move(actor, CDirectionType::EDirection::ED_Up, 0);
}

bool CPhisicalEngine::move(CActor* actor, CDirectionType::EDirection direct, int steps)
{
    int shiftX = actor->getCollider()->getShiftX();
    int shiftY = actor->getCollider()->getShiftY();

    int newShiftX = shiftX;
    int newShiftY = shiftY;

    switch(direct)
    {
        case CDirectionType::ED_Down:
        {
            newShiftY += steps;
        }
        break;
        case CDirectionType::ED_Up:
        {
            newShiftY -= steps;
        }
        break;
        case CDirectionType::ED_Left:
        {
            newShiftX -= steps;
        }
        break;
        case CDirectionType::ED_Right:
        {
            newShiftX += steps;
        }
        break;
    }

    // Apply new position.
    ICollider* actorCollider = actor->getCollider();
    actorCollider->setShiftX(newShiftX);
    actorCollider->setShiftY(newShiftY);

    // Try to make rollback.
    bool isStaticCollision = procedStaticCollisionExist(actor);
    bool isDynamicCollision = procedDynamicCollisionExist(actor);
    if(isStaticCollision || isDynamicCollision)
    {
        actorCollider->setShiftX(shiftX);
        actorCollider->setShiftY(shiftY);
        return false;
    }

    return true;
}
