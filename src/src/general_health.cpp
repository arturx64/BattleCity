#include "general_health.h"

using namespace BattleCity;

CGeneralHealth::CGeneralHealth(QObject* parent)
    : QObject(parent)
    , m_enemyHealth(ENEMY_START_HEALTH)
    , m_playerHealth(PLAYER_START_HEALTH)
{
}

void CGeneralHealth::killEnemy()
{
    if(m_enemyHealth > 0)
    {
        --m_enemyHealth;
        emit enemyHealthChanged();
    }
}

void CGeneralHealth::killPlayer()
{
    if(m_playerHealth > 0)
    {
        --m_playerHealth;
        emit playerHealthChanged();
    }
}

int CGeneralHealth::getEnemyHealth() const
{
    return m_enemyHealth;
}

int CGeneralHealth::getPlayerHealth() const
{
    return m_playerHealth;
}
