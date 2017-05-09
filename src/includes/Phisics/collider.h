#ifndef COLLIDER_H
#define COLLIDER_H

#include <QObject>

#include "Phisics/collider_interface.h"

namespace BattleCity
{
namespace Phisics
{
class CCollider : public QObject, public ICollider
{
    Q_OBJECT
    Q_INTERFACES(BattleCity::Phisics::ICollider)
public:

    CCollider(QObject* parent = nullptr);

    virtual void setShiftX(int x) override;
    virtual void setShiftY(int y) override;
    virtual int getShiftX() const override;
    virtual int getShiftY() const override;

    virtual Phisics::CChannel::EChannel getChannel() const override;
    virtual void setChannel(CChannel::EChannel channel) override;

    virtual Phisics::CChannel getCollisionChannels() const override;
    virtual void setCollisionChannels(const std::initializer_list<CChannel::EChannel> collisionChannels) override;

protected:

    CChannel::EChannel m_channel;
    CChannel m_collisionChannel;
    int m_shiftX;
    int m_shiftY;
};
}
}

#endif // COLLIDER_H
