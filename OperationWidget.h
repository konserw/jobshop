#ifndef OPERATIONWIDGET_H
#define OPERATIONWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
class QFormLayout;
class QLabel;
class QComboBox;
class QSpinBox;
QT_END_NAMESPACE

class OperationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OperationWidget(qint32 machineCount = 1,QWidget *parent = 0);
    ~OperationWidget();

public slots:
    void setMachines(int);

protected:
    qint32 m_machineCount;

    QFormLayout *formLayout;
    QLabel *label_machine;
    QLabel *label_time;
    QComboBox *machine;
    QSpinBox *time;


};

#endif // OPERATIONWIDGET_H
