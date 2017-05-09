#ifndef CHANNEL_H
#define CHANNEL_H

#include <QVector>
#include <initializer_list>

namespace BattleCity
{
namespace Phisics
{
/**@class CChannel
Phisical channels.
*/
class CChannel
{
public:

    enum EChannel
    {
        eC_Non = 1,
        eC_Wall = 2,
        eC_PlayerTank = 4,
        eC_EnemyTank = 8,
        eC_PlayerProjectile = 16,
        eC_EnemyProjectile = 32,
        eC_Spawn = 64
    };

    CChannel();

    CChannel(const std::initializer_list<EChannel>& flags);

    /**@function setFlags
    Set new flags.
    */
    void setFlags(const std::initializer_list<EChannel>& flags);

    /**@function removeFlags
    Remove flags.
    */
    void removeFlags(const std::initializer_list<EChannel>& flags);

    /**@function setFlag
    Set single flag.
    */
    void setFlag(EChannel flag);

    /**@function removeFlag
    Remove single flag.
    */
    void removeFlag(EChannel flag);

    /**@function isFlag
    @return true if flag is set.
    */
    bool isFlag(EChannel flag) const;

    /**@function getFlags
    @return flags.
    */
    QVector<EChannel> getFlags() const;

private:

    int m_flags;
};
}
}

#endif // CHANNEL_H
