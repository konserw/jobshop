#include "OperationEditor.h"
#include "Operation.h"

#include <QtWidgets>
//#include <QSize>

OperationEditor::OperationEditor(int machineCount, QWidget *parent) :
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

    ui_formLayout->setWidget(1, QFormLayout::LabelRole, ui_machine);

    ui_time = new QSpinBox(this);
    ui_time->setObjectName(QStringLiteral("time"));
    ui_time->setMinimum(0);
    ui_time->setValue(0);
    ui_time->setMaximum(999999);

    ui_formLayout->setWidget(1, QFormLayout::FieldRole, ui_time);
}

OperationEditor::~OperationEditor()
{
}

const Operation& OperationEditor::operation()
{
    ui_time->interpretText();
    m_operation.setTime(ui_time->value());
    m_operation.setMachine(ui_machine->currentIndex());
    return m_operation;
}

void OperationEditor::setOperation(const Operation &operation)
{
    m_operation = operation;
    ui_time->setValue(m_operation.time());
    ui_machine->setCurrentIndex(m_operation.machine());
}

