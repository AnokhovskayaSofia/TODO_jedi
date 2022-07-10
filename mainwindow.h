#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include "qlistmodel.h"
#include "qinfomodel.h"
#include "qprojectmodel.h"
#include "qproject.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

    void on_addInfo_clicked();

private:
    Ui::MainWindow *ui;
    qListModel* taskmodel = new qListModel(this);
    qInfoModel* infomodel = new qInfoModel(this);
    qProjectModel* projectmodel = new qProjectModel(this);

    int LastEvent; //последнее действие

    //Очистка сделанных задач
    void clearTask();

    //Прочтение файла с задачами
    void readTask();
    //Прочтение файла с информацией
    void readInfo();
    //Прочтение файла с проектам
    void readProject();

    //Запись файла с задачами
    void writeTask();
    //Запись файла с информацией
    void writeInfo();
    //Запись файла с проектам
    void writeProject();
    int recWrite(int index, QModelIndex root, qProjectModel* model, QJsonArray* array);



protected:
    bool eventFilter(QObject *obj, QEvent *event);
};
#endif // MAINWINDOW_H
