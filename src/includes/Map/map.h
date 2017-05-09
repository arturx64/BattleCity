#ifndef MAP_H
#define MAP_H

#include <QList>
#include <QAbstractListModel>

#include "GameComponents/wall_actor.h"

namespace BattleCity
{
namespace Map
{
/**@class CMap
This class keeps map as model.
*/
class CMap : public QAbstractListModel
{
    Q_OBJECT

public:

    enum EMapRoles
    {
        TypeRole = Qt::UserRole + 1,
        DamageRole
    };

    CMap(QObject *parent = nullptr);

    /**@function addWall
    Add wall object.
    */
    void addWall(GameComponents::TWallActorShPtr wall);

    /**@function rowCount
    @return rows.
    */
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    /**@function data
    @return model data.
    */
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    /**@function getDataRef
    @return reference to internal map representation.
    */
    QList<GameComponents::TWallActorShPtr>& getDataRef();

protected:

    /**@function roleNames
    @return QML reoles for model
    */
    QHash<int, QByteArray> roleNames() const;

private slots:

    /**@function updateWall
    Refresh UI.
    */
    void updateWall(int index);

private:
    QList<GameComponents::TWallActorShPtr> m_walls;
};
}
}

#endif // MAP_H
