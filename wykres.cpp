#include "wykres.h"
#include "ui_wykres.h"
#include <QDebug>
#include <QtGui>
#include "common.h"
#include <QFileDialog>

wykres::wykres(QWidget *parent, QGraphicsScene *s) :
    QDialog(parent),
    ui(new Ui::wykres)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Podsumowanie obliczeń"));

    ui->pushButton->setText(tr("export do pdf"));

    ui->graphicsView->setScene(s);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(pdf()));

    zadan = 0;
}

wykres::~wykres()
{
    delete ui;
}

void wykres::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void wykres::setText(QString &s)
{
    ui->label->setText(s);
}


void wykres::finished(stat* x)
{
    DEBUG << "ukonczono zadanie: " << x->j();

    s << x;
    zadan++;
}

void wykres::set(int maszyn, int alfa, int beta)
{
    stat* st;
    c=0;
    f=0;
    l=0;
    e=0;
    sum=0;
    int j, cols;
    QTableWidgetItem* it;

    QStringList list;
    list << tr("cj") << tr("fj") << tr("lj") << tr("ej");
    cols = list.count();
    ui->tableWidget->setColumnCount(cols);
    ui->tableWidget->setHorizontalHeaderLabels(list);

    for(int i=0; i<zadan; i++)
    {
        ui->tableWidget->insertRow(i);
        for(int j=0; j<cols; j++)
        {
            it = new QTableWidgetItem("x");
            ui->tableWidget->setItem(i, j, it);
        }
    }
    ui->tableWidget->setRowCount(zadan);

    DEBUG << "zadan: " << zadan;

    foreach(st, s)
    {
        j = st->j() - 1;
        ui->tableWidget->item(j, 0)->setText(QString::number(st->cj()));
        ui->tableWidget->item(j, 1)->setText(QString::number(st->fj()));
        ui->tableWidget->item(j, 2)->setText(QString::number(st->lj()));
        ui->tableWidget->item(j, 3)->setText(QString::number(st->ej()));

        sum += pow(st->lj(), 2) + pow(st->ej(), 2);
        l += st->lj();
        e += st->ej();

        if(st->cj() > c)c = st->cj();
        f += st->fj();
    }

    QGraphicsSimpleTextItem* text;
    QFont font("Arial", 12);
    QGraphicsScene* scene = ui->graphicsView->scene();
    qreal x;
    qreal x0 = 80;
    qreal ym = (maszyn*40)+20;

    for(int i=0; i<c; i+=5)
    {
        x = x0 + dx*i;
        scene->addLine(x, 0, x, ym);
        text = scene->addSimpleText(QString::number(i), font);
        text->setX(x+3);
        text->setY(ym-18);
    }

    x = x0 + dx*c;
    scene->addLine(x, 0, x, ym);
    text = scene->addSimpleText(tr("Cmax = %1").arg(QString::number(c)), font);
    text->setX(x+3);
    text->setY(ym-18);

    f /= zadan;

    QString str;
    str = tr("\nCmax = ");
    str += QString::number(c);
    str += tr("\nFsr = ");
    str += QString::number(f);
    str += tr("\n√[∑(ej^2) + ∑(lj^2)] =");
    str += QString::number(sqrt(sum));
    str += tr("\nα*∑ej + β*∑lj = ");
    str += QString::number((alfa*e) + (beta*l));
    ui->label->setText(str);

    this->showMaximized();
    this->exec();

    ui->tableWidget->clear();
    foreach(st, s)
    {
        delete st;
    }
    s.clear();
    zadan = 0;
}

void wykres::pdf(const QString &filename)
{
    QString fileName;
    QPrinter* printer;
    QFont* font;
    QTextDocument* doc;
    const int margin = 5;
    const int w = 745;                           //szerokosc szkieletu dokumentu
    const int d = (w-5)/2;                       //szerokość kolumny w szkielecie

    if(filename.isNull() || filename.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, tr("Export wyników do pliku PDF"), "", tr("Plik PDF (*.pdf)"));
        if(fileName.isEmpty())return;
    }
    else
        fileName = filename;

    printer = new QPrinter;
    printer->setPaperSize(QPrinter::A4);
    printer->setResolution(300);
    printer->setPageMargins(margin, margin, margin, margin, QPrinter::Millimeter);
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOutputFileName(fileName);

    font = new QFont;
    font->setPointSize(10);
    font->setFamily("Arial");

    QString s;
    s =     "<table>\n"
            "<tr><td width=\""; //polowa dla tabeli
    s +=    QString::number(d);
    s +=    "\">\n"
            "\t<table>\n"
            "\t<thead><tr>\n"
            "\t\t<td>Cj</td>";


    s +=    "</td><td width=\">"; //połowa dla wyznaczników
    s +=    QString::number(d);
    s +=    "\"Cmax = ";

    s +=    "<br />\n"
            "Fśr = ";

    s +=    "<br />\n"
            "<img src = \"\\rownanie1.png\" /> = ";

    s +=    "<br />\n"
            "<img src=\"\\rownanie2.png\" /> = ";

    s +=    "<br />\n"
            "gdzie:<br>\n"
            "alfa = ";

    s +=    "<br />\n"
            "beta = ";


    doc = new QTextDocument;
    doc->setDefaultFont(*font);
    doc->setHtml(s);
    doc->print(printer);


}


