#include "marszruta.h"
#include "ui_marszruta.h"

marszruta::marszruta(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::marszruta)
{
    ui->setupUi(this);

    ui->label_machine->setText(tr("Maszyna"));
    ui->label_time->setText(tr("Czas"));

    m = 1;
    ui->machine->insertItem(0, "m1");

    ui->time->setMinimum(0);
    ui->time->setValue(0);
    ui->time->setMaximum(999999);
}

marszruta::marszruta(qint32 machines, qint32 machine, qint32 time, QWidget *parent):
    QWidget(parent),
    ui(new Ui::marszruta)
{
    ui->setupUi(this);

    ui->label_machine->setText(tr("Maszyna"));
    ui->label_time->setText(tr("Czas"));

    m = machines;
    QString s;
    for(qint32 i=0; i<m; i++)
    {
        s = "m";
        s += QString::number(i+1);
        ui->machine->insertItem(i, s);
    }
    ui->machine->setCurrentIndex(machine-1);

    ui->time->setMinimum(0);
    ui->time->setValue(time);
    ui->time->setMaximum(999999);
}

marszruta &marszruta::operator =(const marszruta &in)
{
    if(this == &in)
        return *this;

    ui->label_machine->setText(tr("Maszyna"));
    ui->label_time->setText(tr("Czas"));

    m = in.m;
    QString s;
    for(qint32 i=0; i<m; i++)
    {
        s = "m";
        s += QString::number(i+1);
        ui->machine->insertItem(i, s);
    }
    ui->machine->setCurrentIndex(in.machine()-1);

    ui->time->setMinimum(0);
    ui->time->setValue(in.time());
    ui->time->setMaximum(999999);

    return *this;
}

marszruta::~marszruta()
{
    delete ui;
}

void marszruta::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void marszruta::setMachines(qint32 nm)
{
    QString s;

    for(qint32 i=m; i>=nm; i--)
        ui->machine->removeItem(i);


    for(qint32 i=m; i<nm; i++)
    {
        s = "m";
        s += QString::number(i+1);
        ui->machine->insertItem(i, s);
    }

    m = nm;
}

qint32 marszruta::machine() const
{
    return ui->machine->currentIndex()+1;
}

qint32 marszruta::time() const
{
    return ui->time->value();
}

qint32 marszruta::machines() const
{
    return m;
}

QDataStream &operator<<(QDataStream &out, const marszruta &mar)
{
    out << mar.machines()
        << mar.machine()
        << mar.time();
    return out;
}

QDataStream &operator>>(QDataStream &in, marszruta* &mar)
{
    qint32 machine, machines, time;
    in >> machines >> machine >> time;
    mar = new marszruta(machines, machine, time);
    return in;
}
