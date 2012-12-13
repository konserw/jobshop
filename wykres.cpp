#include "wykres.h"
#include "ui_wykres.h"
#include <QDebug>
#include <QtGui>
#include "common.h"
#include <QFileDialog>
#include <QtSvg/QSvgGenerator>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QProcess>

wykres::wykres(QWidget *parent, QGraphicsScene *_scene) :
    QDialog(parent),
    ui(new Ui::wykres),
    scene(_scene)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Podsumowanie obliczeń"));

    ui->doPdf->setText(tr("export do pdf"));
    ui->doLatexu->setText(tr("eksport do LaTeXu"));

    texName = new QString;

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    connect(ui->doPdf, SIGNAL(clicked()), this, SLOT(pdf()));
    connect(ui->doLatexu, SIGNAL(clicked()), this, SLOT(latex()));

    zadan = 0;
}

wykres::~wykres()
{
    delete texName;
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
    foreach(st, stats)
    {
        delete st;
    }
    stats.clear();
    zadan = 0;
}

void wykres::bazinga(const QString &filename)   //start cli mode
{
    if(fmt == 1)
        this->pdf(filename);
    else
        this->latex(filename);

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
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Export wyników do pliku PDF"), "", tr("Plik PDF (*.pdf)"));
    if(fileName.isEmpty())return;
    this->pdf(fileName);
}

void wykres::pdf(const QString &filename)
{
    QString s;
    QString file(filename);
    int rc;
    QStringList args;
    QString program("rubber");

    if(file.contains("."))
            file.chop(4);
    if(file.isEmpty())
        file = "unknown_name";
    file += ".tex";

    this->latex(filename);

    s =     "\\documentclass[11pt,a4paper]{article}\n"
            "\\usepackage{polski}\n" //[babel]
            "\\usepackage[utf8]{inputenc}\n"
            "\\usepackage{mathtools}\n"
            "\\usepackage{color}\n"
            "\\usepackage{graphicx}\n"
            "\\usepackage{transparent}\n"
            "\\mathtoolsset{showonlyrefs}\n"
            "\\title{Generated by kSzereg}\n"
            "\\date{}\n"
            "\\begin{document}\n"
            "\t\\input{output/";
    s +=    *texName;
    s +=    "}\n"
            "\\end{document}\n";

    QFile f(file);
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream ts(&f);
    ts.setCodec(QTextCodec::codecForName("UTF-8"));
    ts << s;
    f.close();

    args << "--pdf" << "-I" << "output" << file;
    DEBUG << "command: " << program << " args: " << args;
    rc = QProcess::execute(program, args);
    DEBUG << program << " return code: " << rc;

    args.clear();
    args << "--clean" << file;
    DEBUG << "command: " << program << " args: " << args;
    rc = QProcess::execute(program, args);
    DEBUG << program << " return code: " << rc;
}

void wykres::latex()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Export wyników do LaTeXu"), "", tr("Plik tex (*.tex)"));
    if(fileName.isEmpty())return;
    this->latex(fileName);
}

void wykres::latex(const QString &filename)
{
    QString fileName(filename);
    QString s;
    int j;
    stat* st;

    this->cdOutput();

    if(fileName.contains("."))
            fileName.chop(4);
    if(fileName.isEmpty())
        fileName = "unknown_name";

    QString name = fileName.remove(0, fileName.lastIndexOf("/")+1);      //usunięcie folderu - sama nazwa
    QString svgName = name + ".svg";
    *texName = name + ".tex";
    QString pdfName = name + "_gantt.pdf";

    QSvgGenerator svgGen;
    svgGen.setFileName(svgName);
    svgGen.setSize(QSize(1000, 500));
    svgGen.setViewBox(QRect(0, 0, 1000, 500));
    svgGen.setTitle(tr("Gantt chart"));
    svgGen.setDescription(tr("Gantt chart"));
    QPainter painter(&svgGen);
    scene->render(&painter);
    painter.end();

    s =     "\n%Tabela\n\n"

            "\t\\begin{table}[h]\n"
            "\t\t\\centering\n"
            "\t\t\\begin{tabular}{ | c | c | c | c | c |}\n"
            "\t\t\\hline\n"
            "\t\tj\t& \\(c_j\\)\t& \\(F_j\\)\t& \\(l_j\\)\t& \\(e_j\\)\t\\\\ \\hline\n";

    foreach(st, stats)
    {
        j = st->j() - 1;
        s += "\t\t";
        s += QString::number(j);
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

    s +=    // "\t\t\\hline\n"
            "\t\\end{tabular}\n"
            "\t\\end{table}\n";


    s +=    "\n%Wyznaczniki\n\n"

            "\t\\begin{equation}\n"
            "\t\tC_{max} = ";
    s +=    QString::number(c);
    s +=    "\n"
            "\t\t\\label{eqn:Cmax}\n"
            "\t\\end{equation}\n"
            "\t\\begin{equation}\n"
            "\t\tF_{śr} = ";
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

    s +=    "%wykres w landscape\n"

           "\t\\begin{landscape}\n"
           "\t\\begin{figure}[htb]\n"
           "\t\t\\centering\n"
           "\t\t\\def\\svgwidth{\\columnwidth}\n"
           "\t\t\\input{";
    s +=    pdfName + "_tex}\n"
            "\t\t\\caption{Gantt chart}\n"
            "\t\\end{figure}\n"
            "\t\\end{landscape}\n";


    QFile f(*texName);
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream ts(&f);
    ts.setCodec(QTextCodec::codecForName("UTF-8"));
    ts << s;
    f.close();

    int rc;
    QStringList args;
    QString program("inkscape");

    args << "-z" << "-f" << svgName << "--export-latex" << "--export-pdf" << pdfName << "-D";
    DEBUG << "command: " << program << " args: " << args;
    rc = QProcess::execute(program, args);
    DEBUG << program << " return code: " << rc;

    this->cdBack();
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

void wykres::cdOutput()
{
    cur = new QDir(QDir::current());
    QDir out(*cur);
    out.cd("output");
    QDir::setCurrent(out.path());
}

void wykres::cdBack()
{
    QDir::setCurrent(cur->path());
    delete cur;
}
