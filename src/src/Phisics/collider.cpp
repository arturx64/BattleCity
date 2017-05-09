#include "Phisics/collider.h"

using namespace BattleCity::Phisics;

CCollider::CCollider(QObject* parent)
    : QObject(parent)
    , m_shiftX(0)
    , m_shiftY(0)
    , m_channel(CChannel::eC_Non)
{

}

CChannel CCollider::getCollisionChannels() const
{
    return m_collisionChannel;
}

void CCollider::setCollisionChannels(const std::initializer_list<CChannel::EChannel> collisionChannels)
{
    m_collisionChannel = collisionChannels;
}

CChannel::EChannel CCollider::getChannel() const
{
    return m_channel;
}

void CCollider::setChannel(CChannel::EChannel channel)
{
    m_channel = channel;
}

void CCollider::setShiftX(int x)
{
    m_shiftX = x;
}

void CCollider::setShiftY(int y)
{
    m_shiftY = y;
}

int CCollider::getShiftX() const
{
    return m_shiftX;
}

int CCollider::getShiftY() const
{
    return m_shiftY;
}
