#ifndef QPROJECTMODEL_H
#define QPROJECTMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QTreeView>
#include "qproject.h"

class qProjectModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit qProjectModel(QObject *parent = nullptr);

    virtual QModelIndex parent(const QModelIndex &child) const override;
    int findRow(const QObject *ProjectInfo) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QObject* objByIndex(const QModelIndex &index) const;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void addItem(QObject* item, const QModelIndex &parent);
//    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void setupModelData(const QStringList &lines, qProject *parent);

    QObject* rootItem;
    QList<qProject> _projects;

};

#endif // QPROJECTMODEL_H
