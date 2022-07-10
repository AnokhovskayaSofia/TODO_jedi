#include "qtask.h"
#include <QDate>

qTask::qTask()
{
    value = "value";
    checked = false;
    lasttime = QDateTime(QDate(22, 5, 30));
}

void qTask::setValue(QString text)
{
    value = text;
}

void qTask::setTime(QDateTime &time)
{
    lasttime = time;
}

void qTask::setChecked(bool check)
{
    checked = check;
}
