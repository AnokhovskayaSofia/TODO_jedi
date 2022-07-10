#ifndef QTASKDELIGATE_H
#define QTASKDELIGATE_H
#include <QObject>
#include <QStyledItemDelegate>


class qTaskDeligate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit qTaskDeligate(QObject *parent = nullptr);

    //Создание виджета редактора значений
    QWidget* createEditor(QWidget *parent, const QStyledItemDelegate &option, const QModelIndex &index) const;

    //Передает значение из модели в редактор
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    //Передает значение от редактора в модели
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    //Задает геометрию редактора
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //Отрисовывает ячейку элемента
    void paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex &index) const;
};

#endif // QTASKDELIGATE_H
