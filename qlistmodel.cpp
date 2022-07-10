#include "qlistmodel.h"
#include <QSize>
#include <QFont>

qListModel::qListModel(QObject *parent) : QAbstractListModel(parent)
{

}

int qListModel::rowCount(const QModelIndex &parent) const
{
    return tasks.count();
}

QVariant qListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return tasks.at(index.row()).value;
    case Qt::SizeHintRole:
        return QSize(0,30);
    case Qt::ToolTipRole:
        return tasks.at(index.row()).value;
    case Qt::FontRole:
    {
        QFont font("Arial", 13);
        if(tasks.at(index.row()).checked)
        {
            font.setStrikeOut(true);
        }

        return font;
    }
    case Qt::CheckStateRole:
        if(tasks.at(index.row()).checked)
            return Qt::Checked;
        return Qt::Unchecked;

    default:
        return QVariant();
    }
}

bool qListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole){
        qTask task;
        task.setValue(value.toString());
        tasks.replace(index.row(), task);
    }
    else if(role == Qt::CheckStateRole){
        bool check = false;
        if ((Qt::CheckState)value.toInt() == Qt::Checked)
               check = true;

        qTask task = tasks.at(index.row());
        task.checked = check;
        tasks.replace(index.row(), task);
    }
}

Qt::ItemFlags qListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    else if (tasks.at(index.row()).checked)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable ;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable ;
}

void qListModel::add(qTask &task)
{
    beginInsertRows(QModelIndex(), tasks.size(), tasks.size());
    tasks.push_front(task);
    endInsertRows();
}

void qListModel::remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    tasks.move(index, 0);
    tasks.pop_front();
    endRemoveRows();
}
