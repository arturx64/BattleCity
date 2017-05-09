#include "game.h"

using namespace BattleCity;

const QString CGame::QML_MAIN_PATH = "qrc:/qml/Main.qml";

CGame::CGame(QObject* parent)
    : QObject(parent)
    , m_gamePlay(nullptr)
{
    m_qmlEngine.load(QUrl(QML_MAIN_PATH));

    QObject *item = m_qmlEngine.rootObjects().at(0);
    if(item)
    {
        QObject::connect(item, SIGNAL(gameStarted()), this, SLOT(startGame()));
    }
}

void CGame::startGame()
{
    createGamePlay();
    m_gamePlay->startGame();
}

void CGame::createGamePlay()
{
    if(!m_gamePlay)
    {
        m_gamePlay = new CGamePlay(&m_qmlEngine, this);
        connect(m_gamePlay, &CGamePlay::restart, this, &CGame::restart);
    }
}

void CGame::destroyGamePlay()
{
    if(m_gamePlay)
    {
        m_gamePlay->deleteLater();
        m_gamePlay = nullptr;
    }
}

void CGame::restart()
{
    destroyGamePlay();

    QObject *item = m_qmlEngine.rootObjects().at(0);
    if(item)
    {
        QMetaObject::invokeMethod(item, "restartGame");
    }
}
