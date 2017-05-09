#include "Phisics/channel.h"

using namespace BattleCity::Phisics;

CChannel::CChannel()
    : m_flags(0)
{
    setFlag(eC_Non);
}

CChannel::CChannel(const std::initializer_list<EChannel>& flags )
    : m_flags(0)
{
    setFlags(flags);
}

void CChannel::setFlags(const std::initializer_list<EChannel>& flags)
{
    for (const auto flag : flags)
    {
        setFlag(flag);
    }
}

void CChannel::removeFlags(const std::initializer_list<EChannel>& flags)
{
    for (const auto flag : flags)
    {
        removeFlag(flag);
    }
}

void CChannel::setFlag(EChannel flag)
{
    m_flags |= flag;
}

void CChannel::removeFlag(EChannel flag)
{
    auto negFlag = ~flag;
    m_flags &= negFlag;
}

bool CChannel::isFlag(EChannel flag) const
{
    return m_flags & flag;
}

 QVector<CChannel::EChannel> CChannel::getFlags() const
 {
     QVector<EChannel> flagsRes;
     if(isFlag(eC_Non)) flagsRes.append(eC_Non);
     if(isFlag(eC_Wall)) flagsRes.append(eC_Wall);
     if(isFlag(eC_PlayerTank)) flagsRes.append(eC_PlayerTank);
     if(isFlag(eC_EnemyTank)) flagsRes.append(eC_EnemyTank);
     if(isFlag(eC_PlayerProjectile)) flagsRes.append(eC_PlayerProjectile);
     if(isFlag(eC_EnemyProjectile)) flagsRes.append(eC_EnemyProjectile);
     return flagsRes;
 }
