#include "wykres.h"
#include "ui_wykres.h"
#include <QDebug>
#include <QtGui>
#include "common.h"
#include <QFileDialog>

wykres::wykres(QWidget *parent, QGraphicsScene *_scene) :
    QDialog(parent),
    ui(new Ui::wykres),
    scene(_scene)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Podsumowanie obliczeń"));

    ui->pushButton->setText(tr("export do pdf"));

    ui->graphicsView->setScene(scene);
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

void wykres::setText(const QString &text)
{
    ui->label->setText(text);
}


void wykres::finished(stat* x)
{
    DEBUG << "ukonczono zadanie: " << x->j();

    stats << x;
    zadan++;
}

void wykres::set(int _maszyn, double _alfa, double _beta)
{
    maszyn = _maszyn;
    alfa = _alfa;
    beta = _beta;

    evalStats();
    setupScene();
}

void wykres::bazinga()  //start gui mode
{
    int j, cols;
    QTableWidgetItem* it;
    QStringList list;
    stat* st;

    list << tr("cj") << tr("fj") << tr("lj") << tr("ej");
    cols = list.count();
    ui->tableWidget->setColumnCount(cols);
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->setRowCount(zadan);
    for(int i=0; i<zadan; i++)
    {
        for(int j=0; j<cols; j++)
        {
            it = new QTableWidgetItem("x");
            ui->tableWidget->setItem(i, j, it);
        }
    }

    foreach(st, stats)
    {
        j = st->j() - 1;
        ui->tableWidget->item(j, 0)->setText(QString::number(st->cj()));
        ui->tableWidget->item(j, 1)->setText(QString::number(st->fj()));
        ui->tableWidget->item(j, 2)->setText(QString::number(st->lj()));
        ui->tableWidget->item(j, 3)->setText(QString::number(st->ej()));
    }

    QString str;
    str = tr("\nCmax = ");
    str += QString::number(c);
    str += tr("\nFsr = ");
    str += QString::number(f);
    str += tr("\n√[∑(ej^2) + ∑(lj^2)] =");
    str += QString::number(w1);
    str += tr("\nα*∑ej + β*∑lj = ");
    str += QString::number(w2);
    ui->label->setText(str);

    this->showMaximized();
    this->exec();

    ui->tableWidget->clear();
    foreach(st, stats)
    {
        delete st;
    }
    stats.clear();
    zadan = 0;
}

void wykres::bazinga(const QString &filename)   //start cli mode
{
    this->pdf(filename);

    stat* st;
    foreach(st, stats)
    {
        delete st;
    }
    stats.clear();
    zadan = 0;
}

void wykres::pdf() //bo do connecta jest potrzeban funkcja bezargumentowa
{
    this->pdf(NULL);
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

    QPainter p(printer);
    scene->render(&p, printer->pageRect(), scene->sceneRect());
    p.end();

    stat* st;
    QString s;

    s =     "<table>\n"
            "<tr><td width=\"";     //polowa dla tabeli
    s +=    QString::number(d);
    s +=    "\">\n"
            "\t<table>\n"
            "\t<thead><tr>\n"
            "\t\t<td>Lp</td>\n"
            "\t\t<td>Cj</td>\n"
            "\t\t<td>Fj</td>\n"
            "\t\t<td>Lj</td>\n"
            "\t\t<td>Ej</td>\n"
            "\t</tr></thead>\n";
    int j;
    foreach(st, stats)
    {
        j = st->j() - 1;
        s += "\t<tr>\n"
             "\t\t<td>";
        s += QString::number(j);
        s += "</td>\n";
        s += "\t\t<td>";
        s += QString::number(st->cj());
        s += "</td>\n";
        s += "\t\t<td>";
        s += QString::number(st->fj());
        s += "</td>\n";
        s += "\t\t<td>";
        s += QString::number(st->lj());
        s += "</td>\n";
        s += "\t\t<td>";
        s += QString::number(st->ej());
        s += "</td>\n"
             "\t</tr>\n";
    }

    s +=    "\t</table>\n"
            "</td><td width=\"";    //połowa dla wyznaczników
    s +=    QString::number(d);
    s +=    "\">\n\tCmax = ";
    s +=    QString::number(c);
    s +=    "<br />\n"
            "\tFśr = ";
    s +=    QString::number(f);
    s +=    "<br />\n"
            "\t<img src = \"\\rownanie1.png\" /> = ";
    s +=    QString::number(w1);
    s +=    "<br />\n"
            "\t<img src=\"\\rownanie2.png\" /> = ";
    s +=    QString::number(w2);
    s +=    "<br />\n"
            "\tgdzie:<br>\n"
            "\talfa = ";
    s +=    QString::number(alfa);
    s +=    "<br />\n"
            "\tbeta = ";
    s +=    QString::number(beta);
    s +=    "\n</td></tr></table>";

    doc = new QTextDocument;
    doc->setDefaultFont(*font);
    doc->setHtml(s);
 //   doc->print(printer);


    delete printer;
    delete font;
    delete doc;
}

void wykres::evalStats()
{
    stat* st;
    c = 0;
    f = 0;
    l = 0;
    e = 0;
    double sum = 0;

    foreach(st, stats)
    {
        sum += pow(st->lj(), 2) + pow(st->ej(), 2);
        l += st->lj();                              //sum lejts
        e += st->ej();                              //sum earliness

        if(st->cj() > c)c = st->cj();               //find Cmax
        f += st->fj();                              //evaluate mean flow time
    }
    f /= zadan;

    w1 = sqrt(sum);
    w2 = (alfa*e) + (beta*l);

}

void wykres::setupScene()
{
    QGraphicsSimpleTextItem* text;
    QFont font("Arial", 12);
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

}


