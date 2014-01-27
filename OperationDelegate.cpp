#include "OperationDelegate.h"
#include "OperationWidget.h"
#include "Operation.h"
#include "JobshopModel.h"

OperationDelegate::OperationDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *OperationDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    if(!index.isValid() || index.column() < jobModel->nonOperationColumns() || index.column() >= jobModel->columnCount())
        return new QWidget(parent);

    OperationWidget* editor = new OperationWidget(jobModel->machinesCount(), parent);
    return editor;
}

void OperationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(!index.isValid() || index.column() < jobModel->nonOperationColumns() || index.column() >= jobModel->columnCount())
        return;

    OperationWidget* editor = qobject_cast<OperationWidget*>(editor);
   // spinBox->setValue(index.model()->data(index, Qt::EditRole).toDouble());
}

void OperationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(!index.isValid() || index.column() < jobModel->nonOperationColumns() || index.column() >= jobModel->columnCount())
        return;
/*
    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor);
    spinBox->interpretText();
    double count = spinBox->value();
    model->setData(index, count, Qt::EditRole);
    */
}

void OperationDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
