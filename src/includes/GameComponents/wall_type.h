#ifndef WALL_TYPE_H
#define WALL_TYPE_H

#include <QObject>

namespace BattleCity
{
namespace GameComponents
{
class CWallType : public QObject
{
    Q_OBJECT

    public:
        enum EWallType
        {
            EWT_Non,
            EWT_Bricks,
            EWT_Metall,
            EWT_Eagle
        };
        Q_ENUMS(EWallType)

        static void declareQML();
};
}
}

#endif // WALL_TYPE_H
