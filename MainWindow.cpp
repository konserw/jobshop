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
#include "EvolutionWindow.h"

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

    Jobshop* job = Jobshop::instance();
    m_model = job->model();

    ui->tableView->setModel(m_model);
    ui->tableView->setItemDelegate(new OperationDelegate(this));
//    ui->tableView->verticalHeader()->sectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setDefaultSectionSize(60);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(125);


/*
    connect(ui->rout, &QSpinBox::valueChanged, job, &Jobshop::setOperationsCount);
    connect(ui->machines, &QSpinBox::valueChanged, Jobshop::instance(), &Jobshop::setMachinesCount);
*/
    connect(ui->machines, SIGNAL(valueChanged(int)), job, SLOT(setMachinesCount(int)));
    connect(ui->rout, SIGNAL(valueChanged(int)), Jobshop::instance(), SLOT(setOperationsCount(int)));

    connect(ui->importButton, &QPushButton::clicked, this, &MainWindow::imp);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::exp);
    connect(ui->solve, &QPushButton::clicked, this, &MainWindow::solve);
    connect(ui->more, &QPushButton::clicked, this, &MainWindow::addJob);

//demodata
/*
    ui->machines->setValue(5);
    ui->rout->setValue(5);
    ui->more->click();
    ui->more->click();
    ui->more->click();
*/
    import("sample.mar");
    //Jobshop::instance()->solve();
    this->solve();
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

void MainWindow::import(const QString& s)
{
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

    m_model->loadModel(in);

    qDebug() <<  "koniec wczytywania";

    ui->machines->setValue(Jobshop::instance()->machinesCount());
    ui->rout->setValue(Jobshop::instance()->operationsCount());

    ui->solve->setEnabled(true);
    ui->exportButton->setEnabled(true);
    ui->importButton->setEnabled(false);
}


void MainWindow::imp()
{
    QString s;
    s = QFileDialog::getOpenFileName(this, tr("Otwórz plik marszrut"), "", tr("Plik mar (*.mar)"));
    if(s.isEmpty())return;

    import(s);
}

void MainWindow::solve()
{
    EvolutionWindow* evo = new EvolutionWindow(this);
    connect(Jobshop::instance(), &Jobshop::iteration, evo, &EvolutionWindow::plot);
    evo->showMaximized();
    Jobshop::instance()->solve();
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

    Jobshop::instance()->save(out);

    qDebug() <<  "koniec zapisu";
}
