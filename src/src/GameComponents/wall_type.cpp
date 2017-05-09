#include "GameComponents/wall_type.h"

#include <QtQml>

using namespace BattleCity::GameComponents;

// Declare your class to the QML system.
void CWallType::declareQML()
{
    qmlRegisterType<BattleCity::GameComponents::CWallType>("EWallTypeEnum", 1, 0, "EWallType");
}
