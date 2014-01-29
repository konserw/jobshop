#include "OperationDelegate.h"
#include "OperationWidget.h"
#include "Operation.h"
#include "JobshopModel.h"
#include "Jobshop.h"

OperationDelegate::OperationDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *OperationDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex &index) const
{
    if(index.data().canConvert<Operation>())
        return new OperationWidget(Jobshop::instance()->machinesCount(), parent);
    else
        return QStyledItemDelegate::createEditor(parent, option, index);

    /*
    if(!index.isValid() || index.row() >= Jobshop::instance()->rowCount() || index.column() >= Jobshop::instance()->columnCount())
        return new QWidget(parent);

    if(index.column() < Jobshop::instance()->nonOperationColumns())
        return QStyledItemDelegate::createEditor(parent, option, index);

    return new OperationWidget(Jobshop::instance()->machinesCount(), parent);
*/
}

void OperationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.data().canConvert<Operation>())
    {
        Operation operation = qvariant_cast<Operation>(index.data());
        OperationWidget* widget = qobject_cast<OperationWidget*>(editor);
        widget->setOperation(operation);
    }
    else
        QStyledItemDelegate::setEditorData(editor, index);

    /*
    if(!index.isValid() || index.column() < Jobshop::instance()->nonOperationColumns() || index.column() >= Jobshop::instance()->columnCount())
        return;

    OperationWidget* widget = qobject_cast<OperationWidget*>(editor);
    Operation* operation = static_cast<Operation*>(index.internalPointer());
    widget->setWidgetData(operation->machine(), operation->time());
    */
}

void OperationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.data().canConvert<Operation>())
    {
        OperationWidget* widget = qobject_cast<OperationWidget*>(editor);
        model->setData(index, QVariant::fromValue(widget->operation()));
    }
    else
        QStyledItemDelegate::setModelData(editor, model, index);


    /*
    if(!index.isValid() || index.column() < Jobshop::instance()->nonOperationColumns() || index.column() >= Jobshop::instance()->columnCount())
        return;

    OperationWidget* widget = qobject_cast<OperationWidget*>(editor);
    Operation* operation = static_cast<Operation*>(index.internalPointer());
    operation->setMachine(widget->machine());
    operation->setTime(widget->time());
    */
}

void OperationDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

QSize OperationDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.data().canConvert<Operation>())
    {/*
        StarRating starRating = qvariant_cast<StarRating>(index.data());
        return starRating.sizeHint();
        */
    }
    else
        return QStyledItemDelegate::sizeHint(option, index);
}
