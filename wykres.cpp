#include "wykres.h"
#include "ui_wykres.h"
#include <QDebug>
#include <QtGui>
#include "common.h"
#include <QFileDialog>
#include <QtSvg/QSvgGenerator>
#include <QtAlgorithms>
#include <QList>
#include "zadanie.h"


wykres::wykres(QWidget *parent, QGraphicsScene *_scene) :
    QDialog(parent),
    ui(new Ui::wykres),
    scene(_scene)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Podsumowanie obliczeń"));

    ui->doPdf->setText(tr("export do pdf"));
    ui->doLatexu->setText(tr("eksport do LaTeXu"));

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    connect(ui->doPdf, SIGNAL(clicked()), this, SLOT(pdf()));
    connect(ui->doLatexu, SIGNAL(clicked()), this, SLOT(latex()));

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

void wykres::bazinga(const QList<zadanie*> *zad)  //start gui mode
{
    DEBUG << "bazinga gui mode";

    zadania = zad;

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
    str = tr("<br>Cmax = ");
    str += QString::number(c);
    str += tr("<br>Fsr = ");
    str += QString::number(f);
    str += "<br><img src=:/w1> = ";
    str += QString::number(w1);
    str += "<br><img src=:/w2> = ";
    str += QString::number(w2);
    ui->label->setTextFormat(Qt::RichText);
    ui->label->setStyleSheet("QLabel { background-color : white; color : black; }");
    ui->label->setText(str);

    this->showMaximized();
    this->exec();

    ui->tableWidget->clear();
    this->clean();
}

void wykres::bazinga(const QString &fileName, const QList<zadanie*> *zad)   //start cli mode
{
    zadania = zad;

    QFileInfo fi(fileName);
    const QString name = tr("output/%1.tex").arg(fi.baseName());

    DEBUG << "bazinga pliku: " << fileName;

    if(fmt == 1)
        this->pdf(name);
    else
        this->latex(name);

    this->clean();
}

void wykres::pdf()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Export wyników do pliku PDF"), "", tr("Plik PDF (*.pdf)"));
    if(fileName.isEmpty())return;

    this->pdf(fileName);
}

void wykres::pdf(const QString &fileName)
{
    const QString texFile("output/wrapped.tex");

    this->latex("output/temp.tex");

    QString s;
    s =     "\\documentclass[11pt,a4paper]{article}\n"
            "\\usepackage{polski}\n" //[babel]
            "\\usepackage[utf8]{inputenc}\n"
            "\\usepackage{mathtools}\n"
            "\\usepackage{color}\n"
            "\\usepackage{graphicx}\n"
            "\\usepackage{lscape}\n"
            "\\usepackage{transparent}\n"
            "\\mathtoolsset{showonlyrefs}\n"
            "\\title{Generated by kSzereg}\n"
            "\\date{}\n"
            "\\begin{document}\n"
            "\t\\input{";
    s +=    "temp.tex";
    s +=    "}\n"
            "\\end{document}\n";

    save(texFile, s);

    QStringList args;
    args << "--pdf" << "--inplace" << "-I" << "output" << texFile;
    run("rubber", args);

    args.clear();
    args << "--clean" << "--inplace" << texFile;
    run("rubber", args);

    QDir::current().rename("output/wrapped.pdf", fileName);
}

void wykres::latex()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Export wyników do LaTeXu"), "", tr("Plik tex (*.tex)"));
    if(fileName.isEmpty())return;
    this->latex(fileName);
}

void wykres::latex(const QString &texName)
{
    QString s;
    stat* st;

    QFileInfo fi(texName);
    const QString name = fi.baseName();
    const QString svgName(tr("output/gantt_%1.svg").arg(name));
    const QString pdfName(tr("gantt_%1.pdf").arg(name));

    QSvgGenerator svgGen;
    svgGen.setFileName(svgName);
    svgGen.setSize(QSize(1000, 500));
    svgGen.setViewBox(QRect(0, 0, 1000, 500));
    svgGen.setTitle(tr("Gantt chart"));
    svgGen.setDescription(tr("Gantt chart"));
    QPainter painter(&svgGen);
    scene->render(&painter);
    painter.end();

    QStringList args;
    args << "-z" << "-f" << svgName << "--export-latex" << "--export-pdf" << tr("output/%1").arg(pdfName) << "-D";
    run("inkscape", args);

    s =     "\n%Tabela danych\n\n"
            "\t\\begin{table}[htb]\n"
            "\t\t\\centering\n"
            "\t\t\\begin{tabular}{ | r | c | c | l | }\n"
            "\t\t\\hline\n"
            "\t\tj\t& \\(r_j\\)\t& \\(d_j\\)\t& Marszruta technologiczna\t\\\\ \\hline\n";
    zadanie* z;
    foreach(z, *zadania)
    {
        s += "\t\t";
        s += QString::number(z->number());
        s += "\t& ";
        s += QString::number(z->arrive());
        s += "\t& ";
        s += QString::number(z->due());
        s += "\t& ";
        s += z->print();
        s += "\t\\\\ \\hline\n";
    }
    s +=    "\t\t\\end{tabular}\n"
            "\t\t\\caption{Dane wejściowe}\n"
            "\t\\end{table}\n";

    s +=    "\n%Tabela wynikowa\n\n"
            "\t\\begin{table}[htb]\n"
            "\t\t\\centering\n"
            "\t\t\\begin{tabular}{ | r | c | c | c | c |}\n"
            "\t\t\\hline\n"
            "\t\tj\t& \\(c_j\\)\t& \\(f_j\\)\t& \\(l_j\\)\t& \\(e_j\\)\t\\\\ \\hline\n";

    qSort(stats.begin(), stats.end(), PtrLess<stat>());

    foreach(st, stats)
    {
        s += "\t\t";
        s += QString::number(st->j());
        s += "\t& ";
        s += QString::number(st->cj());
        s += "\t& ";
        s += QString::number(st->fj());
        s += "\t& ";
        s += QString::number(st->lj());
        s += "\t& ";
        s += QString::number(st->ej());
        s += "\t\\\\ \\hline\n";
    }

    s +=    "\t\t\\end{tabular}\n"
            "\t\t\\caption{Parametry wykonanych zleceń}\n"
            "\t\\end{table}\n";

    s +=    "\n%Tabela wyznacznikow\n\n"
            "\t\\begin{table}[htb]\n"
            "\t\t\\centering\n"
            "\t\t\\begin{tabular}{ l l}\n"
            "\t\t\\(C_{max} = ";
    s +=    QString::number(c);
    s +=    " \\)\t& \\(\\sqrt{(\\sum e_j^2 + \\sum l_j^2} = ";
    s +=    QString::number(w1);
    s +=    "\\)\t\\\\\n"
            "\t\t\\(\\bar{F} = ";
    s +=    QString::number(f);
    s +=    " \\)\t& \\(\\left.\\alpha*\\sum e_j + \\beta*\\sum l_j\\right\\big|_{\\substack{\\alpha = ";
    s +=    QString::number(alfa);
    s +=    "\\\\ \\beta = ";
    s +=    QString::number(beta);
    s +=    "}} = ";
    s +=    QString::number(w2);
    s +=    " \\)\t\\\\ \n";

    s +=    "\t\t\\end{tabular}\n"
    //        "\t\t\\caption{Parametry wykonanych zleceń}\n"
            "\t\\end{table}\n";

/*
    s +=    "\n%Wyznaczniki\n\n"
            "\t\\begin{equation}\n"
            "\t\tC_{max} = ";
    s +=    QString::number(c);
    s +=    "\n"
            "\t\t\\label{eqn:Cmax}\n"
            "\t\\end{equation}\n"
            "\t\\begin{equation}\n"
            "\t\t\\bar{F} = ";
    s +=    QString::number(f);
    s +=    "\n"
            "\t\t\\label{eqn:Fsr}\n"
            "\t\\end{equation}\n"
            "\t\\begin{equation}\n"
            "\t\t\\sqrt{(\\sum e_j^2 + \\sum l_j^2} = ";
    s +=    QString::number(w1);
    s +=    "\n"
            "\t\t\\label{eqn:w1}\n"
            "\t\\end{equation}\n"
            "\t\\begin{equation}\n"
            "\t\t\\alpha*\\sum e_j + \\beta*\\sum l_j = ";
    s +=    QString::number(w2);
    s +=    ",\n"
            "\t\t\\label{eqn:w2}\n"
            "\t\\end{equation}\n"
            "\tgdzie\n"
            "\t\\begin{equation}\n"
            "\t\t\\alpha = ";
    s +=    QString::number(alfa);
    s +=    ",\\quad\\beta = ";
    s +=    QString::number(beta);
    s +=    "\n"
            "\t\\end{equation}\n";
*/
    s +=    "%wykres w landscape\n"
           "\t\\begin{landscape}\n"
           "\t\\begin{figure}[htb]\n"
           "\t\t\\centering\n"
           "\t\t\\def\\svgwidth{\\columnwidth}\n"
           "\t\t\\input{";
    s +=    pdfName + "_tex}\n"
            "\t\t\\caption{Wykres Gantt'a}\n"
            "\t\\end{figure}\n"
            "\t\\end{landscape}\n";

    save(texName, s);
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
        l += st->lj();                              //sum lates
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

void wykres::clean()
{
    stat* st;
    foreach(st, stats)
    {
        delete st;
    }
    stats.clear();
    zadan = 0;
}
