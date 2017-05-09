#include "GameComponents/actor.h"

using namespace BattleCity::GameComponents;
using namespace BattleCity::Phisics;

CActor::CActor(QObject* parent)
    : QObject(parent)
{
}

void CActor::onHit(CActor*)
{
    // Do nothing.
}

void CActor::callHitSignal()
{
    emit hit(this);
}
