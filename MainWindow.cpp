#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Operation.h"
#include "JobshopModel.h"
#include "Job.h"
#include "Result.h"
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

    this->setWindowIcon(QIcon(":/logo"));

    JobshopModel* model = Jobshop::instance()->model();

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new OperationDelegate(this));
    ui->tableView->verticalHeader()->setDefaultSectionSize(60);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(125);

    connect(ui->spinBox_machines, SIGNAL(valueChanged(int)), Jobshop::instance(), SLOT(setMachinesCount(int)));
    connect(ui->spinBox_population, SIGNAL(valueChanged(int)), Jobshop::instance(), SLOT(setPopulation(int)));
    connect(ui->spinBox_crossovers, SIGNAL(valueChanged(int)), Jobshop::instance(), SLOT(setCrossovers(int)));

    connect(ui->comboBox_fitness, SIGNAL(currentIndexChanged(int)), model, SLOT(setFitnessFunction(int)));
    connect(ui->spinBox_operations, SIGNAL(valueChanged(int)), model, SLOT(setOperationsCount(int)));
    connect(ui->spinBox_jobs, SIGNAL(valueChanged(int)), model, SLOT(setJobsCount(int)));
    connect(ui->demodataButton, &QPushButton::clicked, model, &JobshopModel::demodata);

    connect(ui->importButton, &QPushButton::clicked, this, &MainWindow::imp);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::exp);
    connect(ui->solveButton, &QPushButton::clicked, this, &MainWindow::solve);

    ui->spinBox_machines->setMaximum(99);
    ui->spinBox_machines->setMinimum(1);
    ui->spinBox_machines->setValue(1);

    ui->spinBox_operations->setMaximum(99);
    ui->spinBox_operations->setMinimum(0);
    ui->spinBox_operations->setValue(0);

    ui->spinBox_jobs->setMaximum(99);
    ui->spinBox_jobs->setMinimum(0);
    ui->spinBox_jobs->setValue(0);

    ui->spinBox_population->setMaximum(9999);
    ui->spinBox_population->setMinimum(2);
    ui->spinBox_population->setValue(24);

    ui->spinBox_crossovers->setMaximum(999);
    ui->spinBox_crossovers->setMinimum(1);
    ui->spinBox_crossovers->setValue(6);

    ui->comboBox_fitness->addItems(model->fitnessFunctions());

     //demodata
/*
    ui->spinBox_machines->setValue(5);
    ui->spinBox_jobs->setValue(10);
    ui->spinBox_operations->setValue(10);
    Jobshop::instance()->demodata();
*/
    import("sample.mar");
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

void MainWindow::import(const QString& s)
{
    qDebug() <<  "Loading jobshop scheduling problem from file" << s;

    QFile file(s);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Nie udało się otworzyć pliku z danymi marszrut"));
        if(!file.exists()) qWarning() <<  "File does not exist";
        else qWarning() <<  "File is not aviable";
        return;
    }

    QDataStream in(&file);

    Jobshop::instance()->model()->loadModel(in);

    ui->spinBox_machines->setValue(Jobshop::instance()->machinesCount());
    ui->spinBox_jobs->setValue(Jobshop::instance()->jobCount());
    ui->spinBox_operations->setValue(Jobshop::instance()->operationsCount());

    ui->spinBox_crossovers->setValue(Jobshop::instance()->crossovers());
    ui->spinBox_population->setValue(Jobshop::instance()->population());
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
    if(Jobshop::instance()->jobCount() == 0 || Jobshop::instance()->operationsCount() == 0)
    {
        //todo dokladniejsze sprawdzenie czy jest co liczyc
        QMessageBox::warning(this, tr("Error"), tr("Please provide some jobs and operations."));
        return;
    }

    EvolutionWindow evo(this);
    evo.showMaximized();
    evo.exec();
}

void MainWindow::exp()
{
    QString s;
    s = QFileDialog::getSaveFileName(this, tr("Zapisz plik marszrut"), "", tr("Plik mar (*.mar)"));
    if(s.isEmpty())return;

    qDebug() <<  "Saving jobshop scheduling problem to file" << s;

    QFile file(s);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Nie udało się otworzyć pliku z danymi marszrut"));
        qWarning() <<  "File is not aviable for writting";
        return;
    }

    QDataStream out(&file);

    Jobshop::instance()->save(out);
}
