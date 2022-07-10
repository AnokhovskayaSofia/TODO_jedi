#include "qprojectmodel.h"
#include "qproject.h"

qProjectModel::qProjectModel(QObject *parent):
    QAbstractItemModel(parent),
    rootItem(new QObject(this))
{

}

QObject* qProjectModel::objByIndex(const QModelIndex &index) const
{
    if (!index.isValid())
       return rootItem;
    return static_cast<QObject*>(index.internalPointer());
}

QVariant qProjectModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return objByIndex(index)->property("Name");
    case Qt::EditRole:
    {
        QObject *curObject = new qProject();
        for(auto& propertyName: objByIndex(index)->dynamicPropertyNames())
            curObject->setProperty(propertyName, objByIndex(index)->property(propertyName));
        QVariant variant;
        variant.setValue<QObject*>(curObject);
        return variant;
    }
    case Qt::SizeHintRole:
        return QSize(0,30);
    case Qt::ToolTipRole:
        return objByIndex(index)->property("Name");
    case Qt::FontRole:
    {
        QFont font("Arial", 13);
        return font;
    }

    default:
        return QVariant();
    }
}

bool qProjectModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    beginResetModel();
    if(role == Qt::EditRole){
//        QObject* firstChild = new qProject(value.toString(), objByIndex(index)->parent());
        objByIndex(index)->setProperty("Name", value.toString());
//        tasks.replace(index.row(), task);
        endResetModel();
        return true;
    }
    endResetModel();
    return false;
}

void qProjectModel::addItem(QObject *item, const QModelIndex &parent)
{
    beginInsertRows(parent, rowCount(parent), rowCount(parent));

    item->setParent(objByIndex(parent));

    endInsertRows();
}

QModelIndex qProjectModel::parent(const QModelIndex &child) const
{
        QObject* childInfo = objByIndex(child);
        QObject* parentInfo = childInfo->parent();
        if(parentInfo == rootItem)
            return QModelIndex();

        QObject* grandParantObj = parentInfo->parent();
        int row = grandParantObj->children().indexOf(parentInfo);

//        int row =1;
        return createIndex(row, 0, parentInfo);

}
int qProjectModel::findRow(const QObject *ProjectInfo) const
{

}

int qProjectModel::rowCount(const QModelIndex &parent) const
{

  return objByIndex(parent)->children().count();
}

int qProjectModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}


QModelIndex qProjectModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
       return QModelIndex();
    QObject *_parent = objByIndex(parent);
    return createIndex(row, column, _parent->children().at(row));
}

