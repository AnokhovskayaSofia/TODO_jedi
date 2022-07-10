#ifndef QTASK_H
#define QTASK_H

#include <QObject>
#include <QDateTime>

class qTask
{

public:
    qTask();

    bool checked;
    QDateTime lasttime;
    QString value;

    //Задание значения
    void setValue(QString text);

    //Задание значения времени
    void setTime(QDateTime &time);

    //Задание значения выполнения
    void setChecked(bool check);
};

#endif // QTASK_H
