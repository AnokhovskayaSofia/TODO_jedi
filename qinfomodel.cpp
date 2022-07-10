#include "qinfomodel.h"
#include <QSize>
#include <QFont>
#include <QIcon>

qInfoModel::qInfoModel(QObject *parent) : QAbstractListModel(parent)
{
    setIconVector();
}

int qInfoModel::rowCount(const QModelIndex &parent) const
{
    return information.count();
}

QVariant qInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return information.at(index.row()).value;
    case Qt::SizeHintRole:
        return QSize(0,30);
    case Qt::ToolTipRole:
        return information.at(index.row()).value;
    case Qt::FontRole:
    {
        QFont font("Arial", 13);
        return font;
    }
    case Qt::DecorationRole:{
        int id = index.row();
        int num = information.at(index.row()).numIcon;

        QIcon ico = QIcon(myIcons.at(information.at(index.row()).numIcon));
        return QIcon(myIcons.at(information.at(index.row()).numIcon));
    }
    default:
        return QVariant();
    }
}

bool qInfoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole){
        qInformation info;
        info.setValue(value.toString());
        information.replace(index.row(), info);
    }
    else if(role == Qt::DecorationRole ){

    }
}

Qt::ItemFlags qInfoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

                         return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable ;
                     }

void qInfoModel::add(qInformation &info)
{
    beginInsertRows(QModelIndex(), information.size(), information.size());
    information.push_front(info);
    endInsertRows();
}

void qInfoModel::setIconVector()
{
    myIcons.clear();
    myIcons.push_back(":/book-alt-free-icon-font.png");
    myIcons.push_back(":/browser-free-icon-font.png");
    myIcons.push_back(":/film-free-icon-font.png");
    myIcons.push_back(":/marker-free-icon-font.png");
    myIcons.push_back(":/bookmark-free-icon-font.png");
}
