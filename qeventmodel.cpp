#include "qeventmodel.h"
#include "QFont"

qEventModel::qEventModel(QObject *parent)
{

}

int qEventModel::rowCount(const QModelIndex &parent) const
{
    return events.count();
}

QVariant qEventModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return events.at(index.row()).value;
    case Qt::SizeHintRole:
        return QSize(0,30);
    case Qt::ToolTipRole:
        return events.at(index.row()).value;
    case Qt::FontRole:
    {
        QFont font("Arial", 13);
        return font;
    }
    default:
        return QVariant();
    }
}

bool qEventModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

Qt::ItemFlags qEventModel::flags(const QModelIndex &index) const
{

}

void qEventModel::add(QEvent &event)
{

}

void qEventModel::remove(int index)
{

}
