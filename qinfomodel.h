#ifndef QINFOMODEL_H
#define QINFOMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "qinfo.h"

class qInfoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit qInfoModel(QObject *parent = nullptr);

    QVector<QString> myIcons;

    //Колво элементов
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    //Значение элемента
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    //Сохранить новое значение
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    //Возвращает параметры редактируемости элемента
    Qt::ItemFlags flags(const QModelIndex & index) const;

    //Создание нового элемента
    void add(qInformation &info);

    //Удаление элемента
    void remove( int index);

    //Заполнение иконок
    void setIconVector();

    QList<qInformation> information;

signals:

};

#endif // QINFOMODEL_H
