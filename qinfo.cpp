#include "qinfo.h"
#include "QUrl"
qInformation::qInformation()
{
    numIcon = 1;
    value = "Информация";
}

void qInformation::setValue(QString text)
{
    value = text;
}

void qInformation::setIconNum(int num)
{
    numIcon = num;
}
