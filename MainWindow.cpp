#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Operation.h"
#include "JobshopModel.h"
#include "Job.h"
#include "common.h"
#include "result.h"
#include "ResultWindow.h"

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
    ui->more->setEnabled(false);

    ui->label_machines->setText(tr("Ilość maszyn"));
    ui->machines->setMaximum(90);
    ui->machines->setMinimum(1);
    ui->machines->setValue(1);

    ui->label_rout->setText(tr("Długość marszruty"));
    ui->rout->setMaximum(90);
    ui->rout->setMinimum(0);
    ui->rout->setValue(0);

    connect(ui->more, SIGNAL(clicked()), &m_model, SLOT(addJob()));
    connect(ui->more, SIGNAL(clicked()), this, SLOT(setSolveEnabled()));
    connect(ui->solve, SIGNAL(clicked()), this, SLOT(solve()));
    connect(ui->rout, SIGNAL(valueChanged(int)), this, SLOT(rout(int)));
    connect(ui->exportButton, SIGNAL(clicked()), this, SLOT(exp()));
    connect(ui->importButton, SIGNAL(clicked()), this, SLOT(import()));
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

void MainWindow::rout(int col)
{
    ui->more->setEnabled(col);

    m_model.setOperationsCount(col);
}

void MainWindow::solve()
{
    /*
    skonczone = 0;
    t = 0;
    maszyna* m;
    zadanie* z;
    qint32 i;
    qint32 zadan, maszyn;

    ui->centralWidget->setEnabled(false);

    for(i=0; i<ui->machines->value(); i++)
    {
        m = new maszyna(i+1, scene);
        connect(this, SIGNAL(tick()), m, SLOT(update()));
        connect(this, SIGNAL(tick2()), m, SLOT(up2()));
        maszyny.append(m);
    }
    maszyn = i;

    for(i=0; i<ui->tableWidget->rowCount(); i++)
    {
        z = new zadanie(i+1, ui->tableWidget->item(i, 1)->text().toInt(), ui->tableWidget->item(i, 2)->text().toInt());
        for(qint32 j=3; j<ui->tableWidget->columnCount(); j++)
            z->add_rout(qobject_cast<marszruta*>(ui->tableWidget->cellWidget(i, j)));

        connect(z, SIGNAL(next(qint32,zadanie*)), this, SLOT(next(qint32,zadanie*)));
        connect(z, SIGNAL(finished(Result*)), this, SLOT(finished(Result*)));
        connect(z, SIGNAL(finished(Result*)), gant, SLOT(finished(Result*)));
        connect(this, SIGNAL(tick()), z, SLOT(update()));

        zadania.append(z);
    }
    zadan = i;

    do
    {
        emit tick();
        emit tick2();
        t++;
    }while(zadan > skonczone);

    gant->set(maszyn, ui->alfa->value(), ui->beta->value());
    if(cli)
        gant->bazinga(arg, &zadania);
    else
        gant->bazinga(&zadania);

    foreach(z, zadania)
        delete z;
    foreach(m, maszyny)
        delete m;

    zadania.clear();
    maszyny.clear();

    scene->clear();

    ui->centralWidget->setEnabled(true);
    */
}

void MainWindow::setSolveEnabled()
{
    if(!ui->solve->isEnabled())
    {
        ui->rout->setEnabled(false);
        ui->solve->setEnabled(true);
        ui->exportButton->setEnabled(true);
        ui->importButton->setEnabled(false);
    }
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

    in >> m_model;

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

    out << m_model;

    qDebug() <<  "koniec zapisu";
}
