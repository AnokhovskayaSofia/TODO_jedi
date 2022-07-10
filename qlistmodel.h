#ifndef QLISTMODEL_H
#define QLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "qtask.h"

class qListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit qListModel(QObject *parent = nullptr);

    //Колво элементов
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    //Значение элемента
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    //Сохранить новое значвение
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    //Возвращает параметры редактируемости элемента
    Qt::ItemFlags flags(const QModelIndex & index) const;

    //Создание нового элемента
    void add(qTask &task);

    //Удаление элемента
    void remove( int index);

    QList<qTask> tasks;

signals:

};

#endif // QLISTMODEL_H
