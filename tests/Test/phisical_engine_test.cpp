#include "phisical_engine_test.h"

#include <QVector>
#include <QString>
#include <QPair>
#include <QtTest>

using namespace BattleCity::GameComponents;

#define VERIFY_SECTION_ID(current, expected) \
    QVERIFY2(current == expected, QString("Incorrect section id. Current section id: %1. Expected section id: %2").arg( QString::number(current),  QString::number(expected)).toStdString().c_str());

CPhisicalEngineFixture::CPhisicalEngineFixture( int size, int sections)
    : m_size(size)
    , m_sections(sections)
{
    m_ph.initMap(m_size, sections);

    for(int index = 0; index < m_sections; ++index)
        for(int jndex = 0; jndex < m_sections; ++jndex)
        {
            TBrickWallShPtr actor = CActor::create<TBrickWallShPtr>(QRect(index * 150, jndex * 150, 0, 0), 0);
            m_actors.append(actor);
            m_ph.addStaticObject(actor);
        }
}

BattleCity::Phisics::CPhisicalEngine& CPhisicalEngineFixture::getPhisicsRef()
{
    return m_ph;
}

int CPhisicalEngineFixture::getSize() const
{
    return m_size;
}

int CPhisicalEngineFixture::getSections() const
{
    return m_sections;
}

void CPhisicalEngineTest::checkAllBorders()
{
    // Arrange.
    CPhisicalEngineFixture fixture(600, 4);
    QVector<TActorWkPtr> actors;
    int sectionSz = fixture.getSize() / fixture.getSections();

    // Act.
    for(int index = 0; index < (fixture.getSections() * fixture.getSections()); ++index)
    {
        actors.append( fixture.getPhisicsRef().getActorBySectionId(index) );
    }

    // Assert.
    for(int index = 0; index < actors.length(); ++index)
    {
        int x = index % fixture.getSections();
        int y = index / fixture.getSections();

        TActorShPtr strongRef = actors[index].toStrongRef();
        if(strongRef)
        {
            QVERIFY2(strongRef->getCollider()->getShiftX() == x * sectionSz, "Actor is incorrect according to X position. Index:" + index );
            QVERIFY2(strongRef->getCollider()->getShiftY() == y * sectionSz, "Actor is incorrect according to Y position. Index:" + index );
        }
    }
}

void CPhisicalEngineTest::checkPositions()
{
    // Arrange.
    CPhisicalEngineFixture fixture(600, 4);
    QVector<QPair<TBrickWallShPtr, int>> data = QVector<QPair<TBrickWallShPtr, int>>()
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(0,   601, 0, 0), 0), -1)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(601, 601, 0, 0), 0), -1)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(601, 0,   0, 0), 0), -1)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(0,   600, 0, 0), 0), 12)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(0,   599, 0, 0), 0), 12)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(0,   598, 0, 0), 0), 12)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(600, 600, 0, 0), 0), 15)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(599, 599, 0, 0), 0), 15)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(598, 598, 0, 0), 0), 15)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(-1,  0,   0, 0), 0), -1)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(0,  -1,   0, 0), 0), -1)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(-1, -1,   0, 0), 0), -1)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(0,   0,   0, 0), 0), 0)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(1,   1,   0, 0), 0), 0)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(149, 149, 0, 0), 0), 0)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(150, 150, 0, 0), 0), 5)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(460, 100, 0, 0), 0), 3)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(450, 300, 0, 0), 0), 11)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(460, 150, 0, 0), 0), 7)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(0,   455, 0, 0), 0), 12)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(149, 455, 0, 0), 0), 12)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(150, 455, 0, 0), 0), 13)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(299, 455, 0, 0), 0), 13)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(300, 455, 0, 0), 0), 14)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(449, 455, 0, 0), 0), 14)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(450, 455, 0, 0), 0), 15)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(599, 455, 0, 0), 0), 15)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(285, 330, 0, 0), 0), 9)
            << qMakePair(CActor::create<TBrickWallShPtr>(QRect(999, 975, 0, 0), 0), -1);
    QVector<QPair<int, int>> responses;

    // Act.
    for(const auto& actorData: data)
    {
        responses.append(qMakePair(fixture.getPhisicsRef().getSectionIdByActor(actorData.first), actorData.second));
    }

    // Assert.
    for(const auto& response: responses)
    {
        VERIFY_SECTION_ID(response.first, response.second);
    }
}

