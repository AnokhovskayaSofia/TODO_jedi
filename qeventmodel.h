#ifndef QEVENTMODEL_H
#define QEVENTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "qproject.h"
#include "qevent.h"

class qEventModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit qEventModel(QObject *parent = nullptr);

    //Колво элементов
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    //Значение элемента
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    //Сохранить новое значвение
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    //Возвращает параметры редактируемости элемента
    Qt::ItemFlags flags(const QModelIndex & index) const;

    //Создание нового элемента
    void add(qEvent &event);

    //Удаление элемента
    void remove( int index);

    QList<qEvent> events;

};

#endif // QEVENTMODEL_H
