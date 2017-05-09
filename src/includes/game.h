#ifndef GAME_H
#define GAME_H

#include <QQmlApplicationEngine>
#include <QObject>
#include "game_play.h"

namespace BattleCity
{
class CGame : public QObject
{
    Q_OBJECT

public:

    CGame(QObject* parent = nullptr);

private slots:

    void restart();

private slots:

    void startGame();

private:

    void createGamePlay();
    void destroyGamePlay();

    QQmlApplicationEngine m_qmlEngine;
    CGamePlay* m_gamePlay;

    static const QString QML_MAIN_PATH;

};
}

#endif // GAME_H
