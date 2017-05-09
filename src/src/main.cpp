#include <QGuiApplication>

#include <QTime>
#include <QtGlobal>

#include "GameComponents/wall_type.h"
#include "game.h"
#include "direction.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qsrand(QTime::currentTime().msec());
    BattleCity::GameComponents::CWallType::declareQML();
    BattleCity::CDirectionType::declareQT();

    BattleCity::CGame game;
    //game.startGame();

    return app.exec();
}
