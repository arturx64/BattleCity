#ifndef HIT_VISITOR_H
#define HIT_VISITOR_H

#include <QRect>
#include <QHash>
#include <QPair>

namespace BattleCity
{
namespace Phisics
{

// Forward declaration.
class CRectCollider;
class CTabularCollider;

class CHitVisitor
{
public:

    CHitVisitor(CRectCollider* sourceCollider);
    CHitVisitor(CTabularCollider* sourceCollider);

    void visit(CRectCollider* collider);
    void visit(CTabularCollider* collider);

    bool isCollide() const;
   // QRect getRectColliderData() const;
   // QHash<int, QRect> getTabularColliderData() const;

private:

    bool isRectRectCollide(CRectCollider* source, CRectCollider* target) const;
    int isRectTableCollide(CRectCollider* source, CTabularCollider* target) const;
    QPair<int,int> isTableTableCollide(CTabularCollider* source, CTabularCollider* target) const;

    CRectCollider* m_sourceRectCollider;
    CTabularCollider* m_sourceTabularCollider;
    bool m_isCollide;
   // QRect m_rectColliderData;
   // QHash<int, QRect> m_tabularColliderData;

};
}
}

#endif // HIT_VISITOR_H
