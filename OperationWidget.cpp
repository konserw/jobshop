#include "OperationWidget.h"
#include "Operation.h"

#include <QtWidgets>

OperationWidget::OperationWidget(qint32 machineCount, QWidget *parent) :
    QWidget(parent)
{
    m_machineCount = machineCount;

    setObjectName(QStringLiteral("OperationWidget"));
    resize(171, 70);

    formLayout = new QFormLayout(this);
    formLayout->setObjectName(QStringLiteral("formLayout"));
    formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    label_machine = new QLabel(this);
    label_machine->setObjectName(QStringLiteral("label_machine"));
    label_machine->setText(tr("Maszyna"));

    formLayout->setWidget(0, QFormLayout::LabelRole, label_machine);

    label_time = new QLabel(this);
    label_time->setObjectName(QStringLiteral("label_time"));
    label_time->setText(tr("Czas"));

    formLayout->setWidget(0, QFormLayout::FieldRole, label_time);

    machine = new QComboBox(this);
    machine->setObjectName(QStringLiteral("machine"));
    QString s;
    for(qint32 i=0; i<m_machineCount; i++)
    {
        s = "m";
        s += QString::number(i+1);
        machine->insertItem(i, s);
    }
    machine->setCurrentIndex(0);

    formLayout->setWidget(1, QFormLayout::LabelRole, machine);

    time = new QSpinBox(this);
    time->setObjectName(QStringLiteral("time"));
    time->setMinimum(0);
    time->setValue(0);
    time->setMaximum(999999);

    formLayout->setWidget(1, QFormLayout::FieldRole, time);

}

OperationWidget::~OperationWidget()
{/* qwidget zadba?
    delete formLayout;
    delete label_machine;
    delete label_time;
    delete machine;
    delete time;
*/
}

void OperationWidget::setMachines(int nm)
{
    QString s;

    for(qint32 i=m_machineCount; i>=nm; i--)
        machine->removeItem(i);


    for(qint32 i=m_machineCount; i<nm; i++)
    {
        s = "m";
        s += QString::number(i+1);
        machine->insertItem(i, s);
    }

    m_machineCount = nm;
}
