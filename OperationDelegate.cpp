#include "OperationDelegate.h"
#include "OperationEditor.h"
#include "Operation.h"
#include "JobshopModel.h"
#include "Jobshop.h"

#include <QtDebug>

OperationDelegate::OperationDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *OperationDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex &index) const
{
    if(index.data(Qt::EditRole).canConvert<Operation>())
        return new OperationEditor(Jobshop::instance()->machinesCount(), parent);
    else
        return QStyledItemDelegate::createEditor(parent, option, index);
}

void OperationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QVariant& var = index.data(Qt::EditRole);
    if(var.canConvert<Operation>())
    {
        const Operation& operation = qvariant_cast<Operation>(var);
        OperationEditor* widget = qobject_cast<OperationEditor*>(editor);
        widget->setOperation(operation);
    }
    else
        QStyledItemDelegate::setEditorData(editor, index);
}

void OperationDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.data(Qt::EditRole).canConvert<Operation>())
    {
        OperationEditor* widget = qobject_cast<OperationEditor*>(editor);
        model->setData(index, QVariant::fromValue(widget->operation()));
    }
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

void OperationDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
