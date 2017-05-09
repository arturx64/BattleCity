#include "Phisics/tabular_collider.h"

using namespace BattleCity::Phisics;

CTabularCollider::CTabularCollider(QObject* parent)
    : CCollider(parent)
    , m_sections(0)
    , m_lastCollisionId(-1)
    , m_width(0)
    , m_height(0)
{
}

bool CTabularCollider::removeSubColliderById(int id)
{
    return m_colliderStructure.remove(id) > 0;
}

int CTabularCollider::getLastCollisionId() const
{
    return m_lastCollisionId;
}

void CTabularCollider::setLastCollisionId(int lastId)
{
    m_lastCollisionId = lastId;
}

void CTabularCollider::acceptHit(CHitVisitor* visitor)
{
    visitor->visit(this);
}

QHash<int, QRect> CTabularCollider::getTabularColliderData() const
{
    return m_colliderStructure;
}

void CTabularCollider::setRect(const QRect& rect, int sections)
{
    m_sections = sections;

    int sectionW = rect.width() / sections;
    int sectionH = rect.height() / sections;

    for(int index = 0; index < m_sections; ++index)
        for(int jndex = 0; jndex < m_sections; ++jndex)
        {
            int id = m_sections * index + jndex;
            m_colliderStructure.insert(id, QRect(jndex * sectionW, index * sectionH, sectionW, sectionH ));
        }

    calculateSize();
}

bool CTabularCollider::isCollide(ICollider* collider)
{
    CHitVisitor hitVisitor(this);
    collider->acceptHit(&hitVisitor);
    return hitVisitor.isCollide();
}

int CTabularCollider::getWidth() const
{
    return m_width;
}

int CTabularCollider::getHeight() const
{
    return m_height;
}

void CTabularCollider::calculateSize()
{
    int width = 0;
    int height = 0;
    for(QHash<int, QRect>::const_iterator iter = m_colliderStructure.begin(); iter != m_colliderStructure.end(); ++iter )
    {
        int heightTemp = iter.value().y() + iter.value().height();
        int widthTemp = iter.value().x() + iter.value().width();

        if(heightTemp > height)
            height = heightTemp;
        if(widthTemp > width)
            width = widthTemp;
    }
}

