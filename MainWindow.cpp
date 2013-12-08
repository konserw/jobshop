#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Operation.h"
#include "maszyna.h"
#include "Job.h"
#include "common.h"
#include "result.h"
#include <QtDebug>
#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QStringList>

const int startCol = 5;

MainWindow::MainWindow(const QString& arg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("jobshop"));

    this->setWindowIcon(QIcon(":/kico"));
/*
    ui->label_alfa->setText(tr("α"));
    ui->alfa->setMinimum(0);
    ui->alfa->setValue(0.5);
    ui->alfa->setMaximum(1);
    ui->alfa->setSingleStep(0.1);

    ui->label_beta->setText(tr("β"));
    ui->beta->setMinimum(0);
    ui->beta->setValue(0.5);
    ui->beta->setMaximum(1);
    ui->beta->setSingleStep(0.1);
*/
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

    ui->tableWidget->setColumnCount(startCol);
    QStringList labels;
    labels << tr("Nazwa zlecenia") << tr("Czas rozpoczęcia") << tr("Czas zakończenia") << tr("α") << tr("β");
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget->resizeColumnsToContents();

    scene = new QGraphicsScene(this);
    gant = new wykres(this, scene);

    connect(ui->more, SIGNAL(clicked()), this, SLOT(more()));
    connect(ui->solve, SIGNAL(clicked()), this, SLOT(solve()));
    connect(ui->rout, SIGNAL(valueChanged(int)), this, SLOT(rout(int)));
    connect(ui->exportButton, SIGNAL(clicked()), this, SLOT(exp()));
    connect(ui->importButton, SIGNAL(clicked()), this, SLOT(imp()));

    if(cli)
    {
        this->import(arg);
        this->solve(arg);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::rout(qint32 col)
{
    if(!ui->more->isEnabled())
            ui->more->setEnabled(true);

    ui->tableWidget->setColumnCount(startCol + col);
/*
    QStringList labels;
    labels << tr("Nazwa zlecenia") << tr("Czas rozpoczęcia") << tr("Czas zkończenia");
    for(qint32 i=1; i<=col; ++i)
        labels << QString::number(i);
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    */
}

void MainWindow::solve(const QString &arg)
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

void MainWindow::more()
{
    QTableWidgetItem* item;

    if(!ui->solve->isEnabled())
    {
        ui->rout->setEnabled(false);
        ui->solve->setEnabled(true);
        ui->exportButton->setEnabled(true);
        ui->importButton->setEnabled(false);
    }

    qint32 mac = ui->machines->value();
    Operation* mar;
    qint32 rows = ui->tableWidget->rowCount();
    qint32 cols = ui->tableWidget->columnCount();

/*
    ui->tableWidget->insertRow(rows);
    item = new QTableWidgetItem("");
    ui->tableWidget->setItem(rows, 0, item);
    item = new QTableWidgetItem("0");
    ui->tableWidget->setItem(rows, 1, item);
    item = new QTableWidgetItem("0");
    ui->tableWidget->setItem(rows, 2, item);
    for(qint32 i=startCol; i<cols; i++)
    {
        mar = new Operation;
        mar->setMachines(mac);
        connect(ui->machines, SIGNAL(valueChanged(int)), mar, SLOT(setMachines(int)));
        ui->tableWidget->setCellWidget(rows, i, mar);
    }

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
*/
}

void MainWindow::more(const QString& nazwa, qint32 start, qint32 due, const QList<Operation *> &marszruty)
{
    QTableWidgetItem* item;
    Operation* mar;
    qint32 rows = ui->tableWidget->rowCount();
    qint32 cols = ui->tableWidget->columnCount();

    ui->tableWidget->insertRow(rows);
    item = new QTableWidgetItem(nazwa);
    ui->tableWidget->setItem(rows, 0, item);
    item = new QTableWidgetItem(QString::number(start));
    ui->tableWidget->setItem(rows, 1, item);
    item = new QTableWidgetItem(QString::number(due));
    ui->tableWidget->setItem(rows, 2, item);
    for(qint32 i=3; i<cols; i++)
    {
        mar = marszruty[i-3];
//        connect(ui->machines, SIGNAL(valueChanged(int)), mar, SLOT(setMachines(int)));
//        ui->tableWidget->setCellWidget(rows, i, mar);
    }

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::next(qint32 m, Job* z)
{
    maszyny[m-1]->add(z);
}

void MainWindow::finished(Result* x)
{
    qDebug() << "zadanie " << x->j() << "zakonczone";
    skonczone++;
}

void MainWindow::import(const QString &s)
{
    QFile file(s);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Nie udało się otworzyć pliku z danymi marszrut"));
        if(!file.exists()) qWarning() <<  "plik marszrut nie iesnieje";
        else qWarning() <<  "plik marszrut nie jest dostępny";
        return;
    }

    qDebug() <<  "wczytuje marszruty...";

    QDataStream in(&file);

    in >> *this;

    qDebug() <<  "koniec wczytywania";
}

void MainWindow::imp()
{
    QString s;
    s = QFileDialog::getOpenFileName(this, tr("Otwórz plik marszrut"), "", tr("Plik mar (*.mar)"));
    if(s.isEmpty())return;

    import(s);
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

    out << *this;

    qDebug() <<  "koniec zapisu";
}

QDataStream &operator<<(QDataStream &out, const MainWindow &win)
{
    /*
    qint32 tasks = qint32(win.ui->tableWidget->rowCount());
    qint32 routLength = qint32(win.ui->rout->value());

    out << qint32(win.ui->machines->value())                        //nbumber of machines
        << routLength                                               //number of operations for each task
        << tasks                                                    //number of tasks
        << alfa
        << beta;
    for(qint32 i=0; i<tasks; ++i)
    {
        out << win.ui->tableWidget->item(i, 0)->text()              //nazwa
            << win.ui->tableWidget->item(i, 1)->text().toInt()      //start time
            << win.ui->tableWidget->item(i, 2)->text().toInt();     //due date
        for(qint32 j=0; j<routLength; ++j)                          //operations
        {
            out << *qobject_cast<marszruta*>(win.ui->tableWidget->cellWidget(i, j+3));
        }
    }
*/
    return out;
}

QDataStream &operator>>(QDataStream &in, MainWindow &win)
{
    win.ui->rout->setEnabled(false);
    win.ui->solve->setEnabled(true);
    win.ui->exportButton->setEnabled(true);
    win.ui->importButton->setEnabled(false);
/*
    qint32 machines, routLength, tasks;
    qreal alfa, beta;

    in >> machines >> routLength >> tasks;
    win.ui->machines->setValue(machines);
    win.ui->rout->setValue(routLength);

    QList<marszruta*> marszruty;
    marszruta* mar;
    qint32 start, due;
    QString nazwa;

    for(qint32 i=0; i<tasks; ++i)
    {
        in >> nazwa >> start >> due;
        marszruty.clear();
        for(qint32 j=0; j<routLength; ++j)
        {
            in >> mar;
            marszruty.append(mar);
        }
        win.more(nazwa, start, due, marszruty);
    }
*/
    return in;
}
