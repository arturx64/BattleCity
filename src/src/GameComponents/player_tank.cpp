#include "GameComponents/player_tank.h"

#include <QQmlComponent>
#include <QQuickWindow>
#include <QMutableListIterator>

using namespace BattleCity;
using namespace BattleCity::GameComponents;
using namespace BattleCity::Phisics;

CPlayerTank::CPlayerTank(CDirectionType::EDirection direction, QQmlApplicationEngine* engine, const QPoint& spawnPoint, QObject* parent )
    : CTank(direction, spawnPoint, parent)
    , m_timer(nullptr)
{
    m_collider->setChannel(CChannel::eC_PlayerTank);
    m_collider->setCollisionChannels({CChannel::eC_Wall, CChannel::eC_EnemyTank, CChannel::eC_PlayerTank});

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CPlayerTank::updateStep);
    m_timer->start(MOVE_DELAY);

    QQuickWindow *window = qobject_cast<QQuickWindow*>(engine->rootObjects().at(0));
    if (!window)
    {
        qFatal("Can't get window from QML.");
    }
    else
    {
        window->installEventFilter(this);
    }
}

void CPlayerTank::updateStep()
{
    if(!moveDirection.isEmpty())
    {
        CDirectionType::EDirection direction = moveDirection.back();
        m_direction = direction;
        move(m_direction, TANK_SPEED);
        updateUI();
    }
}

void CPlayerTank::onHit(CActor* hitObject)
{
    if(hitObject && hitObject->getCollider()->getChannel() == CChannel::eC_EnemyProjectile)
    {
        QSharedPointer<QQuickItem> item = m_uiItem.toStrongRef();
        if (item)
        {
            (item)->setVisible(false);
        }
        callHitSignal();
    }
}

void CPlayerTank::removeMovement(CDirectionType::EDirection direction)
{
    QMutableListIterator<CDirectionType::EDirection> iter(moveDirection);
    while (iter.hasNext())
    {
        if (iter.next() == direction)
            iter.remove();
    }
}

bool CPlayerTank::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::FocusOut)
    {
        moveDirection.clear();
    }
    else if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( key->key() == Qt::Key_W || key->key() == Qt::Key_Up )
        {
            moveDirection.append(CDirectionType::ED_Up);
        }
        if ( key->key() == Qt::Key_S || key->key() == Qt::Key_Down )
        {
            moveDirection.append(CDirectionType::ED_Down);
        }
        if ( key->key() == Qt::Key_A || key->key() == Qt::Key_Left )
        {
            moveDirection.append(CDirectionType::ED_Left);
        }
        if ( key->key() == Qt::Key_D || key->key() == Qt::Key_Right )
        {
            moveDirection.append(CDirectionType::ED_Right);
        }
        if ( key->key() == Qt::Key_Space )
        {
            int x = m_collider->getShiftX() + m_collider->getWidth() / 2;
            int y = m_collider->getShiftY() + m_collider->getHeight() / 2;
            emit fired(m_direction, QPoint(x, y), this);
        }
    }
    else if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( key->key() == Qt::Key_W || key->key() == Qt::Key_Up )
        {
            removeMovement(CDirectionType::ED_Up);
        }
        if ( key->key() == Qt::Key_S || key->key() == Qt::Key_Down )
        {
            removeMovement(CDirectionType::ED_Down);
        }
        if ( key->key() == Qt::Key_A || key->key() == Qt::Key_Left )
        {
           removeMovement(CDirectionType::ED_Left);
        }
        if ( key->key() == Qt::Key_D || key->key() == Qt::Key_Right )
        {
            removeMovement(CDirectionType::ED_Right);
        }
    }

    return QObject::eventFilter(obj, event);
}
