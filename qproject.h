#ifndef QPROJECT_H
#define QPROJECT_H

#include <QObject>
#include <QList>
#include <QVariant>

class qProject: public QObject
{
public:
    qProject(const QString& _name = "tr", QObject* parent = nullptr):
        QObject(parent),
        value(_name)
    {
        QObject::setProperty("Name" ,_name);
    }

    void appendChild(qProject *child);

    QString value;
    qProject *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    qProject *parentItem();

    //Задание значения
    void setValue(QString text);

    //Задание parent
    void setParent(qProject* parent);

    QList<qProject*> m_childItems;
    QList<QVariant> m_itemData;
    qProject *m_parentItem;



};

#endif // QPROJECT_H
