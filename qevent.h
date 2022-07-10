#ifndef QEVENT_H
#define QEVENT_H

#include <QObject>
#include <QDateTime>
#include <QVariant>

class qEvent
{
public:
    qEvent();

    //Начало события
    QDateTime startDate;
    //Конец события
    QDateTime endDate;
    //Название
    QString value;
    //Тип события
    int type;

    //Задание начала события
    void setStartDate(QVariant startDate, QString startTime);
    //Задание конца события
    void setEndDate(QVariant endDate, QString endTime);
    //Задание названия
    void setValue(QString value);
    //Задание типа события
    void setType(int type);
};

#endif // QEVENT_H
