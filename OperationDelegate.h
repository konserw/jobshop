#ifndef OPERATIONDELEGATE_H
#define OPERATIONDELEGATE_H

#include <QItemDelegate>

/*!
 * \brief The OperationDelegate class - used for editing operation parameters
 */
class OperationDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit OperationDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const;

};

#endif // OPERATIONDELEGATE_H
