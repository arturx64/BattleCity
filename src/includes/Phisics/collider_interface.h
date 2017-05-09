#ifndef COLLIDER_INTERFACE_H
#define COLLIDER_INTERFACE_H

#include <initializer_list>

#include "Phisics/channel.h"
#include "Phisics/hit_visitor.h"

namespace BattleCity
{
namespace Phisics
{
class ICollider
{
public:

    virtual bool isCollide(ICollider* collider) = 0;
    virtual void acceptHit(CHitVisitor* visitor) = 0;

    virtual void setShiftX(int x) = 0;
    virtual void setShiftY(int y) = 0;
    virtual int getShiftX() const = 0;
    virtual int getShiftY() const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    virtual Phisics::CChannel::EChannel getChannel() const = 0;
    virtual void setChannel(CChannel::EChannel channel) = 0;

    virtual Phisics::CChannel getCollisionChannels() const = 0;
    virtual void setCollisionChannels(const std::initializer_list<CChannel::EChannel> collisionChannels) = 0;

};
}
}

Q_DECLARE_INTERFACE(BattleCity::Phisics::ICollider,"ICollider/1.0")

#endif // COLLIDER_INTERFACE_H
