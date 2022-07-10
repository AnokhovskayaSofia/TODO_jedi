#include "qtaskdeligate.h"
#include <QLineEdit>
#include <QApplication>
#include <QCheckBox>
#include <QPainter>


qTaskDeligate::qTaskDeligate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget* qTaskDeligate::createEditor(QWidget *parent, const QStyledItemDelegate &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);


//    Q_UNUSED(option)
//    Q_UNUSED(index)

    //Cоздаем checkbox editor
//    QCheckBox *editor_ = new QCheckBox(parent);
//    return editor_;

    return editor;

}

void qTaskDeligate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    QLineEdit *edit = static_cast<QLineEdit*>(editor);
    edit->setText(value);

//    //Установливаем выбрано/не выбрано
//    QCheckBox *cb = qobject_cast<QCheckBox *>(editor);
//    cb->setChecked(index.data().toBool());
}

void qTaskDeligate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *edit = static_cast<QLineEdit*>(editor);
    QString value = edit->text();
    model->setData(index, value, Qt::EditRole);

//    //Записываем данные в модель
//    QCheckBox *cb = static_cast<QCheckBox *>(editor);
//    int value_ = (cb->checkState()==Qt::Checked)? 1 : 0;
//    model->setData(index, value_, Qt::EditRole);

}

void qTaskDeligate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);

//    Q_UNUSED(index);
//    QStyleOptionButton checkboxstyle;
//    QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkboxstyle);

//    //Центрирование
//    checkboxstyle.rect = option.rect;
//    checkboxstyle.rect.setLeft(option.rect.x() +
//                               option.rect.width()/2 - checkbox_rect.width()/2);

//    editor->setGeometry(checkboxstyle.rect);
}

void qTaskDeligate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    //Получаем данные выполнения
    bool data = index.model()->data(index, Qt::CheckStateRole).toBool();

    //Создаем стиль CheckBox
    QStyleOptionButton checkboxstyle;
    QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkboxstyle);

    //Центрирование
    checkboxstyle.rect = option.rect;
    checkboxstyle.rect.setLeft(option.rect.x() + 10 + checkbox_rect.width()/2);

    //Выбрано или не выбрано
    if(data)
        checkboxstyle.state = QStyle::State_On|QStyle::State_Enabled;
    else
        checkboxstyle.state = QStyle::State_Off|QStyle::State_Enabled;

    //Готово! Отображаем!
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxstyle, painter);


    //Получаем данные текста
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    QRect value_rect = option.rect;

    QFont font("Arial", 13);
    QFontMetrics metrics(font);
    painter->setFont(font);

    value_rect.setLeft(checkbox_rect.right() + 30);
    value_rect.setTop((option.rect.y() + (option.rect.height())/2) - (metrics.height()/2));

    painter->drawText(value_rect, value);
}
