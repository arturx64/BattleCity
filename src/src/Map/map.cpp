#include "Map/map.h"

using namespace BattleCity;
using namespace BattleCity::GameComponents;
using namespace BattleCity::Map;

CMap::CMap(QObject* parent)
    : QAbstractListModel(parent)
{
}

void CMap::addWall(TWallActorShPtr wall)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_walls << wall;
    connect(wall.data(), &TWallActorShPtr::Type::updated, this, &CMap::updateWall );
    endInsertRows();
}

void CMap::updateWall(int indexVal)
{
    emit dataChanged(index(indexVal,0), index(indexVal,0));
}

int CMap::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_walls.count();
}

QVariant CMap::data(const QModelIndex & index, int role) const
{
    if (index.row() < 0 || index.row() >= m_walls.count())
          return QVariant();

      TWallActorShPtr wall = m_walls[index.row()];
      if (role == TypeRole)
      {
          return wall->getType();
      }
      else if (role == DamageRole)
      {
          return wall->getDamage();
      }
      return QVariant();
}

QList<GameComponents::TWallActorShPtr>& CMap::getDataRef()
{
    return m_walls;
}

QHash<int, QByteArray> CMap::roleNames() const
{
    QHash<int, QByteArray> roles;
        roles[TypeRole] = "typeRole";
        roles[DamageRole] = "damageRole";
        return roles;
}
