#include "GameComponents/movable_actor.h"

#include "Phisics/phisical_engine.h"

using namespace BattleCity;
using namespace BattleCity::GameComponents;

CMovableActor::CMovableActor(QObject* parent)
    : CActor(parent)
{
}

bool CMovableActor::move(CDirectionType::EDirection direct, int steps)
{
    bool res = PHISICS.move(this, direct, steps);
    if(res)
    {
        updateUI();
    }
    return res;
}
