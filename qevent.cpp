#include "qevent.h"

qEvent::qEvent()
{
   value = "Событие";
}

void qEvent::setStartDate(QVariant startDate, QString startTime)
{
    this->startDate.setDate(startDate.toDate());
    this->startDate.setTime(QTime(0, 0).addSecs(startTime.toInt()));
}

void qEvent::setEndDate(QVariant endDate, QString endTime)
{
    this->startDate.setDate(endDate.toDate());
    this->startDate.setTime(QTime(0, 0).addSecs(endTime.toInt()));
}

void qEvent::setValue(QString value)
{
    this->value = value;
}

void qEvent::setType(int type)
{
    this->type = type;
}
