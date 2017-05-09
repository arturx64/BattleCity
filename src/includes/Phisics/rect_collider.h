#ifndef RECT_COLLIDER_H
#define RECT_COLLIDER_H

#include <QRect>

#include "Phisics/collider.h"

namespace BattleCity
{
namespace Phisics
{
class CRectCollider : public CCollider
{
    Q_OBJECT

public:

    CRectCollider(QObject* parent = nullptr);

    void setRect(const QRect& rect);
    QRect getRectColliderData() const;

    virtual void acceptHit(CHitVisitor* visitor) override;
    virtual bool isCollide(ICollider* collider) override;

    virtual int getWidth() const override;
    virtual int getHeight() const override;

private:

    QRect m_rect;

};
}
}

#endif // RECT_COLLIDER_H
