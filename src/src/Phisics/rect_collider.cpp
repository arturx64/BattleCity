#include "Phisics/rect_collider.h"

using namespace BattleCity::Phisics;

CRectCollider::CRectCollider(QObject* parent)
    : CCollider(parent)
{
}

void CRectCollider::acceptHit(CHitVisitor* visitor)
{
    visitor->visit(this);
}

QRect CRectCollider::getRectColliderData() const
{
    return m_rect;
}

void CRectCollider::setRect(const QRect& rect)
{
    m_rect = rect;
}

bool CRectCollider::isCollide(ICollider* collider)
{
    CHitVisitor hitVisitor(this);
    collider->acceptHit(&hitVisitor);
    return hitVisitor.isCollide();

}

int CRectCollider::getWidth() const
{
    return m_rect.width();
}

int CRectCollider::getHeight() const
{
    return m_rect.height();
}
