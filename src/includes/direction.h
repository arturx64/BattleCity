#ifndef DIRECTION_H
#define DIRECTION_H

#include <QObject>

namespace BattleCity
{
class CDirectionType : public QObject
{
    Q_OBJECT

    public:
        enum EDirection
        {
            ED_Up,
            ED_Down,
            ED_Left,
            ED_Right
        };

        static void declareQT();
};
}

#endif // DIRECTION_H
