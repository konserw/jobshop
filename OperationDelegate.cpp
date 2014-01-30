#include "OperationDelegate.h"
#include "OperationWidget.h"
#include "Operation.h"
#include "JobshopModel.h"
#include "Jobshop.h"

#include <QtDebug>
#include <QPainter>

OperationDelegate::OperationDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}
/*
void OperationDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QVariant& var = index.data(Qt::EditRole);
    if(var.canConvert<Operation>() && option.state)
    {
        Operation operation = qvariant_cast<Operation>(var);

        if(option.state & QStyle::State_Editing)
            painter->fillRect(option.rect, QColor(Qt::red));//option.palette.highlight());//.background());

        //operation.paint(painter, option.rect, option.palette);
        QStyledItemDelegate::paint(painter, option, index);
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}
*/
QWidget *OperationDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex &index) const
{
    if(index.data(Qt::EditRole).canConvert<Operation>())
        return new OperationWidget(Jobshop::instance()->machinesCount(), parent);
    else
        return QStyledItemDelegate::createEditor(parent, option, index);
}

void OperationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QVariant& var = index.data(Qt::EditRole);
    if(var.canConvert<Operation>())
    {
        const Operation& operation = qvariant_cast<Operation>(var);
        OperationWidget* widget = qobject_cast<OperationWidget*>(editor);
        widget->setOperation(operation);
    }
    else
        QStyledItemDelegate::setEditorData(editor, index);
}

void OperationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.data(Qt::EditRole).canConvert<Operation>())
    {
        OperationWidget* widget = qobject_cast<OperationWidget*>(editor);
        model->setData(index, QVariant::fromValue(widget->operation()));
    }
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

void OperationDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
/*
QSize OperationDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QVariant& var = index.data(Qt::EditRole);
    if(var.canConvert<Operation>())
    {
        const Operation& operation = qvariant_cast<Operation>(var);
        qDebug() << "sizehint";
        return QSize(200, 200);//operation.sizeHint();
    }
    else
        return QStyledItemDelegate::sizeHint(option, index);
}
*/
