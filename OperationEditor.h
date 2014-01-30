#ifndef OPERATIONWIDGET_H
#define OPERATIONWIDGET_H

#include <QWidget>
#include "Operation.h"

QT_BEGIN_NAMESPACE
class QFormLayout;
class QLabel;
class QComboBox;
class QSpinBox;
QT_END_NAMESPACE

/*!
 * \brief The OperationWidget class - it is used by @OperationDelegate to edit operation's properties
 */
class OperationEditor : public QWidget
{
    Q_OBJECT

public:
    explicit OperationEditor(int machineCount = 1, QWidget *parent = 0);
    ~OperationEditor();

//    void setWidgetData(int machine, int time);
//    int machine()const;
//    int time()const;

//    QSize sizeHint() const;

    const Operation &operation();
    void setOperation(const Operation &operation);
/*
public slots:
    void setMachinesCount(int);
*/
protected:
    Operation m_operation;

    int m_machineCount;

    QFormLayout *ui_formLayout;
    QLabel *ui_label_machine;
    QLabel *ui_label_time;
    QComboBox *ui_machine;
    QSpinBox *ui_time;
};

#endif // OPERATIONWIDGET_H
