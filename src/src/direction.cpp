#include "direction.h"

using namespace BattleCity;

void CDirectionType::declareQT()
{
    qRegisterMetaType<CDirectionType::EDirection>("CDirectionType::EDirection");
}
