#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "marszruta.h"
#include "maszyna.h"
#include "zadanie.h"
#include <QStringList>
#include "common.h"

#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>

qint32 t=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList labels;

    this->setWindowTitle(tr("kSzereg"));

    ui->label_alfa->setText(tr("α"));
    ui->label_beta->setText(tr("β"));

    ui->importButton->setText(tr("Import"));
    ui->exportButton->setText(tr("Export"));
    ui->exportButton->setEnabled(false);
    ui->labelDane->setText(tr("Dane:"));

    ui->solve->setText(tr("Rozwiąż"));
    ui->solve->setEnabled(false);
    ui->label_method->setText(tr("Metoda:"));
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

    labels << "FIFO" << "LIFO";
    ui->method->addItems(labels);

    ui->tableWidget->setColumnCount(3);
    labels.clear();
    labels << tr("Nazwa zlecenia") << tr("Czas rozpoczęcia") << tr("Due date");// << "" /*tr("marszruta technologiczna")*/ << "";
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget->resizeColumnsToContents();

    scene = new QGraphicsScene(this);
    gant = new wykres(this, scene);

    connect(ui->more, SIGNAL(clicked()), this, SLOT(more()));
    connect(ui->solve, SIGNAL(clicked()), this, SLOT(solve()));
    connect(ui->rout, SIGNAL(valueChanged(int)), this, SLOT(rout(int)));
    connect(ui->exportButton, SIGNAL(clicked()), this, SLOT(exp()));
    connect(ui->importButton, SIGNAL(clicked()), this, SLOT(imp()));
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

    ui->tableWidget->setColumnCount(3 + col);

    QStringList labels;
    labels << tr("Nazwa zlecenia") << tr("Czas rozpoczęcia") << tr("Due date");
    for(qint32 i=1; i<=col; ++i)
        labels << QString::number(i);// << "" /*tr("marszruta technologiczna")*/ << "";
    ui->tableWidget->setHorizontalHeaderLabels(labels);
}
void MainWindow::solve()
{
    skonczone = 0;
    t = 0;
    maszyna* m;
    zadanie* z;
    qint32 i;
    qint32 zadan, maszyn;

    ui->centralWidget->setEnabled(false);
    maszyna::method = ui->method->currentIndex();

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
        connect(z, SIGNAL(finished(stat*)), this, SLOT(finished(stat*)));
        connect(z, SIGNAL(finished(stat*)), gant, SLOT(finished(stat*)));
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

    foreach(z, zadania)
        delete z;
    foreach(m, maszyny)
        delete m;

    zadania.clear();
    maszyny.clear();

    scene->clear();

    ui->centralWidget->setEnabled(true);
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
    marszruta* mar;
    qint32 rows = ui->tableWidget->rowCount();
    qint32 cols = ui->tableWidget->columnCount();

    ui->tableWidget->insertRow(rows);
    item = new QTableWidgetItem("0");
    ui->tableWidget->setItem(rows, 1, item);
    item = new QTableWidgetItem("0");
    ui->tableWidget->setItem(rows, 2, item);
    for(qint32 i=3; i<cols; i++)
    {
        mar = new marszruta;
        mar->setMachines(mac);
        connect(ui->machines, SIGNAL(valueChanged(qint32)), mar, SLOT(machines(qint32)));
        ui->tableWidget->setCellWidget(rows, i, mar);
    }

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::more(qint32 start, qint32 due, QList<marszruta *> &marszruty)
{
    QTableWidgetItem* item;
    marszruta* mar;
    qint32 rows = ui->tableWidget->rowCount();
    qint32 cols = ui->tableWidget->columnCount();

    ui->tableWidget->insertRow(rows);
    item = new QTableWidgetItem(QString::number(start));
    ui->tableWidget->setItem(rows, 1, item);
    item = new QTableWidgetItem(QString::number(due));
    ui->tableWidget->setItem(rows, 2, item);
    for(qint32 i=3; i<cols; i++)
    {
        mar = marszruty[i-3];
        connect(ui->machines, SIGNAL(valueChanged(qint32)), mar, SLOT(machines(qint32)));
        ui->tableWidget->setCellWidget(rows, i, mar);
    }

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::next(qint32 m, zadanie* z)
{
    maszyny[m-1]->add(z);
}

void MainWindow::finished(stat* x)
{
    DEBUG << "zadanie " << x->j() << "zakonczone"; //, parametry: " << cj << " " << fj << " " << lj;

    skonczone++;
}

void MainWindow::imp()
{
    QString s;
    s = QFileDialog::getOpenFileName(this, tr("Otwórz plik marszrut"), "", tr("Plik mar (*.mar)"));
    if(s.isEmpty())return;

    QFile file(s);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Nie udało się otworzyć pliku z danymi marszrut"));
        if(!file.exists())DEBUG <<  "plik marszrut nie iesnieje";
        else DEBUG <<  "plik marszrut nie jest dostępny";
        return;
    }

    DEBUG <<  "wczytuje marszruty...";

    QDataStream in(&file);

    in >> *this;

    DEBUG <<  "koniec wczytywania";
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
        if(!file.exists())DEBUG <<  "plik marszrut nie iesnieje";
        else DEBUG <<  "plik marszrut nie jest dostępny";
        return;
    }

    DEBUG <<  "zapisuje marszruty...";

    QDataStream out(&file);

    out << *this;

    DEBUG <<  "koniec zapisu";
}


QDataStream &operator<<(QDataStream &out, const MainWindow &win)
{
    qint32 tasks = qint32(win.ui->tableWidget->rowCount());
    qint32 routLength = qint32(win.ui->rout->value());
    qint32 alfa = qint32(win.ui->alfa->value());
    qint32 beta = qint32(win.ui->beta->value());
    out << qint32(win.ui->machines->value())                        //nbumber of machines
        << routLength                                               //number of operations for each task
        << tasks                                                    //number of tasks
        << alfa
        << beta;
    for(qint32 i=0; i<tasks; ++i)
    {
        out << win.ui->tableWidget->item(i, 1)->text().toInt()      //start time
            << win.ui->tableWidget->item(i, 2)->text().toInt();     //due date
        for(qint32 j=0; j<routLength; ++j)                          //operations
        {
            out << *qobject_cast<marszruta*>(win.ui->tableWidget->cellWidget(i, j+3));
        }
    }

    return out;
}

QDataStream &operator>>(QDataStream &in, MainWindow &win)
{
    win.ui->rout->setEnabled(false);
    win.ui->solve->setEnabled(true);
    win.ui->exportButton->setEnabled(true);
    win.ui->importButton->setEnabled(false);

    qint32 machines, routLength, tasks, alfa, beta;

    in >> machines >> routLength >> tasks >> alfa >> beta;
    win.ui->machines->setValue(machines);
    win.ui->rout->setValue(routLength);
    win.ui->alfa->setValue(alfa);
    win.ui->beta->setValue(beta);

    QList<marszruta*> marszruty;
    marszruta* mar;
    qint32 start, due;

    for(qint32 i=0; i<tasks; ++i)
    {
        in >> start >> due;
        marszruty.clear();
        for(qint32 j=0; j<routLength; ++j)
        {
            in >> mar;
            marszruty.append(mar);
        }
        win.more(start, due, marszruty);
    }

    return in;
}


