#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QSaveFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QTextCodec>
#include <QMoveEvent>
#include "qtaskdeligate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TaskView->setModel(taskmodel);
    ui->InfoView->setModel(infomodel);



    QObject* firstParent = new qProject("parent");
    QObject* firstChild = new qProject("child", firstParent);
    QObject* secondChild = new qProject("child2", firstChild);

//    firstParent->setValue("Parent");
//    firstChild->setValue("Child");
    projectmodel->addItem(firstParent, QModelIndex());
//    projectmodel->addItem(firstChild, QModelIndex());
    ui->ProjectView->setModel(projectmodel);
    ui->ProjectView->expandAll();
    ui->ProjectView->header()->hide();

    ui->calendarWidget->setSelectedDate(QDate::currentDate());
//    qTaskDeligate *delegate = new qTaskDeligate(this);
//    ui->TaskView->setItemDelegate(delegate);

    readTask();
    readInfo();
    clearTask();


    this->installEventFilter(this);
    ui->w_Info->hide();
    ui->w_Project->hide();
    connect(this, SIGNAL(clicked()), this, SLOT(opacityBackground()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    qTask task;
    task.setValue("Новая задача");
    taskmodel->add(task);
    writeTask();

}

void MainWindow::on_toolButton_clicked()
{
    clearTask();
    writeTask();
    writeInfo();
    writeProject();
    ui->w_Task->show();
    ui->w_Calendar->show();
    ui->w_Project->hide();
    ui->w_Info->hide();
}

void MainWindow::on_toolButton_2_clicked()
{
    clearTask();
    writeTask();
    writeInfo();
    writeProject();
    ui->w_Task->show();
    ui->w_Calendar->hide();
    ui->w_Project->hide();
    ui->w_Info->hide();
}

void MainWindow::on_toolButton_3_clicked()
{
    writeTask();
    writeInfo();
    writeProject();
    ui->w_Task->hide();
    ui->w_Calendar->show();
    ui->w_Project->hide();
    ui->w_Info->hide();
}

void MainWindow::clearTask()
{
    int count = taskmodel->tasks.size();
    for(auto i=count-1; i>=0; i--)
    {
        if (taskmodel->tasks.at(i).checked)
            taskmodel->remove(i);
    }
}

void MainWindow::readTask()
{
    QByteArray val_;
    QFile file;
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    file.setFileName(QDir::currentPath() + "/Task.json");
    file.open(QFile::ReadOnly | QFile::Text);
    val_ = file.readAll();
    QString val = codec->toUnicode(val_);
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8(), &error);

    if (doc.isObject())
        {
            taskmodel->tasks.clear();
            QJsonObject json = doc.object();
            QJsonArray jsonArray = json["tasks"].toArray();
            foreach (const QJsonValue & value, jsonArray)
                    {
                        if (value.isObject())
                        {
                            QJsonObject obj = value.toObject();
//                            QDateTime time = obj["lasttime"].toString();
                            bool checked = obj["checked"].toBool();
                            QString value = obj["value"].toString();

                            qTask task;
                            task.setValue(value);
//                            task.setTime(time);
                            task.setChecked(checked);
                            taskmodel->add(task);
                        }
                    }
    }
}

void MainWindow::readInfo()
{
    QByteArray val_;
    QFile file;
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    file.setFileName(QDir::currentPath() + "/Info.json");
    file.open(QFile::ReadOnly | QFile::Text);
    val_ = file.readAll();
    QString val = codec->toUnicode(val_);
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8(), &error);

    if (doc.isObject())
        {
            infomodel->information.clear();
            QJsonObject json = doc.object();
            QJsonArray jsonArray = json["info"].toArray();
            foreach (const QJsonValue & value, jsonArray)
                    {
                        if (value.isObject())
                        {
                            QJsonObject obj = value.toObject();
                            int numIcon = obj["numIcon"].toInt();
                            QString value = obj["value"].toString();

                            qInformation info;
                            info.setValue(value);
                            info.setIconNum(numIcon);
                            infomodel->add(info);
                        }
                    }
    }
}

void MainWindow::writeTask()
{

    QJsonArray tasks;
    QJsonObject recordObject;
    for(auto i=0; i<taskmodel->tasks.count(); i++)
    {
        recordObject.insert("lasttime", QJsonValue::fromVariant("1"));
        recordObject.insert("checked", QJsonValue::fromVariant(taskmodel->tasks.at(i).checked));
        recordObject.insert("value", QJsonValue::fromVariant(taskmodel->tasks.at(i).value));
        tasks.push_back(recordObject);
    }

    QJsonObject finalObject;
    finalObject.insert("tasks",tasks);


    QJsonDocument doc(finalObject);
    QString jsonString = doc.toJson(QJsonDocument::Indented);
    QString String = jsonString;
    QFile file;
    file.setFileName(QDir::currentPath() + "/Task.json");

    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream stream( &file );
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        stream << String;
        file.close();
    }
}

void MainWindow::writeInfo()
{
    QJsonArray info;
    QJsonObject recordObject;
    for(auto i=0; i<infomodel->information.count(); i++)
    {
        recordObject.insert("numIcon", QJsonValue::fromVariant(infomodel->information.at(i).numIcon));
        recordObject.insert("value", QJsonValue::fromVariant(infomodel->information.at(i).value));
        info.push_back(recordObject);
    }

    QJsonObject finalObject;
    finalObject.insert("info",info);


    QJsonDocument doc(finalObject);
    QString jsonString = doc.toJson(QJsonDocument::Indented);
    QString String = jsonString;
    QFile file;
    file.setFileName(QDir::currentPath() + "/Info.json");

    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream stream( &file );
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        stream << String;
        file.close();
    }
}

void MainWindow::writeProject()
{
    QJsonArray project;
    QJsonObject recordObject;

    QModelIndex root = ui->ProjectView->rootIndex();
    recWrite(0, root, projectmodel, &project);

    QJsonObject finalObject;
    finalObject.insert("project",project);

    QJsonDocument doc(finalObject);
    QString jsonString = doc.toJson(QJsonDocument::Indented);
    QString String = jsonString;
    QFile file;
    file.setFileName(QDir::currentPath() + "/Project.json");

    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream stream( &file );
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        stream << String;
        file.close();
    }

}

int MainWindow::recWrite(int index, QModelIndex root, qProjectModel* model, QJsonArray* array)
{
    QJsonObject recordObject;

    QModelIndex ind = projectmodel->index(index, 0, root);

    recordObject.insert("value", QJsonValue::fromVariant(projectmodel->objByIndex(ind)->property("Name")));
    recordObject.insert("parent", QJsonValue::fromVariant(projectmodel->objByIndex(ind)->objectName()));
    array->push_back(recordObject);

    if (projectmodel->objByIndex(ind)->children().count())
        recWrite(index, ind, model, array);
    else
        return 1;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::Move)
    {
        setWindowOpacity(0.7);
    }
    else if ((event->type() == QEvent::NonClientAreaMouseButtonRelease && LastEvent == QEvent::Move) || event->type() == QEvent::Show)
    {
        setWindowOpacity(1);
    }
    LastEvent = event->type();

    return QWidget::eventFilter(obj, event);
}



void MainWindow::on_toolButton_4_clicked()
{
    clearTask();
    writeTask();
    writeInfo();
    writeProject();

    ui->w_Project->show();
    ui->w_Task->hide();
    ui->w_Calendar->hide();
    ui->w_Info->hide();

}

void MainWindow::on_toolButton_5_clicked()
{
    clearTask();
    writeTask();
    writeInfo();
    writeProject();

    ui->w_Project->hide();
    ui->w_Task->hide();
    ui->w_Calendar->hide();
    ui->w_Info->show();
}

void MainWindow::on_addInfo_clicked()
{
    qInformation info;
    info.setIconNum(4);
    info.setValue("Новая информация");
    infomodel->add(info);
    writeInfo();
}
