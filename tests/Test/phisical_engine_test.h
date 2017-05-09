#ifndef PHISICAL_ENGINE_TEST_H
#define PHISICAL_ENGINE_TEST_H

#include <QVector>
#include <QString>
#include <QPair>

#include "Phisics/phisical_engine.h"
#include "GameComponents/brick_wall.h"

class CPhisicalEngineFixture
{
public:

    CPhisicalEngineFixture( int size, int sections);
    BattleCity::Phisics::CPhisicalEngine& getPhisicsRef();
    int getSize() const;
    int getSections() const;

    QVector<BattleCity::GameComponents::TBrickWallShPtr> m_actors;
    BattleCity::Phisics::CPhisicalEngine m_ph;

    int m_size;
    int m_sections;
};

class CPhisicalEngineTest : public QObject
{
    Q_OBJECT


private Q_SLOTS:
    void checkAllBorders();
    void checkPositions();
};

#endif // PHISICAL_ENGINE_TEST_H
