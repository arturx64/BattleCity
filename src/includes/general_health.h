#ifndef GENERAL_HEALTH_H
#define GENERAL_HEALTH_H
#include <QObject>
#include <QVector>
#include <QPoint>

#include "GameComponents/spawn_actor.h"

namespace BattleCity
{
class CGeneralHealth : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int enemyHealth READ getEnemyHealth NOTIFY enemyHealthChanged)
    Q_PROPERTY(int playerHealth READ getPlayerHealth NOTIFY playerHealthChanged)

public:

    CGeneralHealth(QObject* parent = nullptr);

    void killEnemy();
    void killPlayer();

    int getEnemyHealth() const;
    int getPlayerHealth() const;

signals:

    void enemyHealthChanged();
    void playerHealthChanged();

private:

    int m_enemyHealth;
    int m_playerHealth;

    static const int ENEMY_START_HEALTH = 20;
    static const int PLAYER_START_HEALTH = 3;
};
}

#endif // GENERAL_HEALTH_H
