#include "OperationWidget.h"
#include "Operation.h"

#include <QtWidgets>

OperationWidget::OperationWidget(int machineCount, QWidget *parent) :
    QWidget(parent)
{
    m_machineCount = machineCount;

    setObjectName(QStringLiteral("OperationWidget"));
    resize(171, 70);

    ui_formLayout = new QFormLayout(this);
    ui_formLayout->setObjectName(QStringLiteral("formLayout"));
    ui_formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    ui_label_machine = new QLabel(this);
    ui_label_machine->setObjectName(QStringLiteral("label_machine"));
    ui_label_machine->setText(tr("Maszyna"));

    ui_formLayout->setWidget(0, QFormLayout::LabelRole, ui_label_machine);

    ui_label_time = new QLabel(this);
    ui_label_time->setObjectName(QStringLiteral("label_time"));
    ui_label_time->setText(tr("Czas"));

    ui_formLayout->setWidget(0, QFormLayout::FieldRole, ui_label_time);

    ui_machine = new QComboBox(this);
    ui_machine->setObjectName(QStringLiteral("machine"));
    for(int i=0; i<m_machineCount; i++)
    {
        ui_machine->addItem(QString("m%1").arg(i+1));
    }
    ui_machine->setCurrentIndex(0);

    ui_formLayout->setWidget(1, QFormLayout::LabelRole, ui_machine);

    ui_time = new QSpinBox(this);
    ui_time->setObjectName(QStringLiteral("time"));
    ui_time->setMinimum(0);
    ui_time->setValue(0);
    ui_time->setMaximum(999999);

    ui_formLayout->setWidget(1, QFormLayout::FieldRole, ui_time);
}

OperationWidget::~OperationWidget()
{
}

void OperationWidget::setWidgetData(int machine, int time)
{
    ui_machine->setCurrentIndex(machine);
    ui_time->setValue(time);
}

int OperationWidget::machine() const
{
    return ui_machine->currentIndex();
}

int OperationWidget::time() const
{
    return ui_time->value();
}

void OperationWidget::setMachinesCount(int nm)
{
    for(qint32 i=m_machineCount; i>=nm; i--)
        ui_machine->removeItem(i);


    for(int i=m_machineCount; i<nm; i++)
    {
        ui_machine->addItem(QString("m%1").arg(i+1));
    }

    m_machineCount = nm;
}
Operation OperationWidget::operation() const
{
    return m_operation;
}

void OperationWidget::setOperation(const Operation &operation)
{
    m_operation = operation;
}

