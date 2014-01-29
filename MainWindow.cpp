#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Operation.h"
#include "JobshopModel.h"
#include "Job.h"
#include "common.h"
#include "result.h"
#include "ResultWindow.h"
#include "OperationDelegate.h"
#include "Jobshop.h"

#include <QtWidgets>
#include <QtDebug>
#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Jobshop scheduling problem resolver"));

    this->setWindowIcon(QIcon(":/kico"));

    ui->importButton->setText(tr("Import"));
    ui->exportButton->setText(tr("Export"));
    ui->exportButton->setEnabled(false);
    ui->labelDane->setText(tr("Dane:"));

    ui->solve->setText(tr("Rozwiąż"));
    ui->solve->setEnabled(false);
    ui->more->setText(tr("Dodaj zlecenie"));

    ui->label_machines->setText(tr("Ilość maszyn"));
    ui->machines->setMaximum(90);
    ui->machines->setMinimum(1);
    ui->machines->setValue(1);

    ui->label_rout->setText(tr("Długość marszruty"));
    ui->rout->setMaximum(90);
    ui->rout->setMinimum(0);
    ui->rout->setValue(0);

    ui->tableView->setModel(Jobshop::instance()->model());
    ui->tableView->setItemDelegate(new OperationDelegate(this));

    Jobshop* job = Jobshop::instance();
/*
    connect(ui->rout, &QSpinBox::valueChanged, job, &Jobshop::setOperationsCount);
    connect(ui->machines, &QSpinBox::valueChanged, Jobshop::instance(), &Jobshop::setMachinesCount);
*/
    connect(ui->machines, SIGNAL(valueChanged(int)), job, SLOT(setMachinesCount(int)));
    connect(ui->rout, SIGNAL(valueChanged(int)), Jobshop::instance(), SLOT(setOperationsCount(int)));

    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::import);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::exp);
    connect(ui->solve, &QPushButton::clicked, Jobshop::instance(), &Jobshop::solve);
    connect(ui->more, &QPushButton::clicked, this, &MainWindow::addJob);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::addJob()
{
    if(!ui->solve->isEnabled())
    {
        ui->solve->setEnabled(true);
        ui->exportButton->setEnabled(true);
        ui->importButton->setEnabled(false);
    }
    Jobshop::instance()->addJob();
}

void MainWindow::import()
{
    QString s;
    s = QFileDialog::getOpenFileName(this, tr("Otwórz plik marszrut"), "", tr("Plik mar (*.mar)"));
    if(s.isEmpty())return;

    QFile file(s);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Nie udało się otworzyć pliku z danymi marszrut"));
        if(!file.exists()) qWarning() <<  "plik marszrut nie iesnieje";
        else qWarning() <<  "plik marszrut nie jest dostępny";
        return;
    }

    qDebug() <<  "wczytuje marszruty z pliku" << s;

    QDataStream in(&file);

    in >> *Jobshop::instance();

    qDebug() <<  "koniec wczytywania";

    ui->rout->setEnabled(false);
    ui->solve->setEnabled(true);
    ui->exportButton->setEnabled(true);
    ui->importButton->setEnabled(false);
}

void MainWindow::exp()
{
    QString s;
    s = QFileDialog::getSaveFileName(this, tr("Zapisz plik marszrut"), "", tr("Plik mar (*.mar)"));
    if(s.isEmpty())return;

    QFile file(s);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Nie udało się otworzyć pliku z danymi marszrut"));
        if(!file.exists()) qWarning() <<  "plik marszrut nie iesnieje";
        else qWarning() <<  "plik marszrut nie jest dostępny";
        return;
    }

    qDebug() <<  "zapisuje marszruty...";

    QDataStream out(&file);

    out << *Jobshop::instance();

    qDebug() <<  "koniec zapisu";
}
