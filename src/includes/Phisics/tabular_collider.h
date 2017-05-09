#ifndef TABULAR_COLLIDER_H
#define TABULAR_COLLIDER_H

#include <QRect>
#include <QHash>

#include "Phisics/collider.h"

namespace BattleCity
{
namespace Phisics
{
class CTabularCollider : public CCollider
{
    Q_OBJECT

public:

    CTabularCollider(QObject* parent = nullptr);

    void setRect(const QRect& rect, int sections);
    bool removeSubColliderById(int id);

    QHash<int, QRect> getTabularColliderData() const;

    int getLastCollisionId() const;
    void setLastCollisionId(int lastId);

    virtual void acceptHit(CHitVisitor* visitor) override;
    virtual bool isCollide(ICollider* collider) override;

    virtual int getWidth() const override;
    virtual int getHeight() const override;

private:

    void calculateSize();

    int m_sections;
    int m_lastCollisionId;
    int m_width;
    int m_height;
    QHash<int, QRect> m_colliderStructure;

};
}
}

#endif // TABULAR_COLLIDER_H
