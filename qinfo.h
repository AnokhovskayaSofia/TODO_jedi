#ifndef QINFO_H
#define QINFO_H
#include <QObject>
#include <QVector>


class qInformation
{
public:
    qInformation();

    int numIcon;
    QString value;

    //Задание значения
    void setValue(QString);

    //Задание иконки
    void setIconNum(int);

};

#endif // QINFO_H
