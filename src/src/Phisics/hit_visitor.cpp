#include "Phisics/hit_visitor.h"

#include "Phisics/rect_collider.h"
#include "Phisics/tabular_collider.h"

using namespace BattleCity::Phisics;

CHitVisitor::CHitVisitor(CRectCollider* sourceCollider)
    : m_sourceRectCollider(sourceCollider)
    , m_isCollide(false)
{

}

CHitVisitor::CHitVisitor(CTabularCollider* sourceCollider)
    : m_sourceTabularCollider(sourceCollider)
    , m_isCollide(false)
{

}

bool CHitVisitor::isCollide() const
{
    return m_isCollide;
}

void CHitVisitor::visit(CRectCollider* collider)
{
    m_isCollide = false;

    if(m_sourceRectCollider && collider)
    {
        m_isCollide = isRectRectCollide(m_sourceRectCollider, collider);
    }
    else if(m_sourceTabularCollider && collider)
    {
        int id = isRectTableCollide(collider, m_sourceTabularCollider);
        if(id != -1)
        {
            m_sourceTabularCollider->setLastCollisionId(id);
            m_isCollide = true;
        }
    }
}

void CHitVisitor::visit(CTabularCollider* collider)
{
    m_isCollide = false;

    if(m_sourceRectCollider && collider)
    {
        int id = isRectTableCollide(m_sourceRectCollider, collider);
        if(id != -1)
        {
            collider->setLastCollisionId(id);
            m_isCollide = true;
        }
    }
    else if(m_sourceTabularCollider && collider)
    {
        QPair<int,int> ids = isTableTableCollide(m_sourceTabularCollider, collider);
        if(ids.first != -1 && ids.second != -1)
        {
            m_sourceTabularCollider->setLastCollisionId(ids.first);
            collider->setLastCollisionId(ids.second);
            m_isCollide = true;
        }
    }
}

bool CHitVisitor::isRectRectCollide(CRectCollider* source, CRectCollider* target) const
{
    if(!source || !target)
        return false;

    QRect rcSource = source->getRectColliderData();
    QRect rcTarget = target->getRectColliderData();
    QRect fullRcSource(source->getShiftX() + rcSource.x(), source->getShiftY() + rcSource.y(), rcSource.width(), rcSource.height());
    QRect fullRcTarget(target->getShiftX() + rcTarget.x(), target->getShiftY() + rcTarget.y(), rcTarget.width(), rcTarget.height());

    return fullRcSource.intersects(fullRcTarget);
}

int CHitVisitor::isRectTableCollide(CRectCollider* source, CTabularCollider* target) const
{
    if(!source || !target)
        return -1;

    QRect rcSource = source->getRectColliderData();
    QRect fullRcSource(source->getShiftX() + rcSource.x(), source->getShiftY() + rcSource.y(), rcSource.width(), rcSource.height());

    QHash<int, QRect> tabularTarget = target->getTabularColliderData();

    for(QHash<int, QRect>::iterator iterTarget = tabularTarget.begin(); iterTarget != tabularTarget.end(); ++iterTarget )
    {
        QRect fullRcTarget(target->getShiftX() + iterTarget.value().x(),
                           target->getShiftY() + iterTarget.value().y(),
                           iterTarget.value().width(),
                           iterTarget.value().height());
        if(fullRcSource.intersects(fullRcTarget))
        {
            return iterTarget.key();
        }
    }

    return -1;
}

QPair<int,int> CHitVisitor::isTableTableCollide(CTabularCollider* source, CTabularCollider* target) const
{
    if(!source || !target)
        return qMakePair(-1,-1);

    QHash<int, QRect> tabularSource = source->getTabularColliderData();
    for(QHash<int, QRect>::iterator iterSource = tabularSource.begin(); iterSource != tabularSource.end(); ++iterSource )
    {
        QRect fullRcSource(source->getShiftX() + iterSource.value().x(),
                           source->getShiftY() + iterSource.value().y(),
                           iterSource.value().width(),
                           iterSource.value().height());

        QHash<int, QRect> tabularTarget = target->getTabularColliderData();
        for(QHash<int, QRect>::iterator iterTarget = tabularTarget.begin(); iterTarget != tabularTarget.end(); ++iterTarget )
        {
            QRect fullRcTarget(target->getShiftX() + iterTarget.value().x(),
                               target->getShiftY() + iterTarget.value().y(),
                               iterTarget.value().width(),
                               iterTarget.value().height());
            if(fullRcSource.intersects(fullRcTarget))
            {
                return qMakePair(iterSource.key(),iterTarget.key());
            }
        }
    }

    return qMakePair(-1,-1);;
}
