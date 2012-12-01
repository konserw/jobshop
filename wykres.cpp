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
    QString sys;
    QString s;

    QDir cur = QDir::current();
    QDir out(cur);
    out.cd("output");
    QDir::setCurrent(out.path());

    if(filename.isNull() || filename.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, tr("Export wyników do pliku PDF"), "", tr("Plik PDF (*.pdf)"));
        if(fileName.isEmpty())return;
    }
    else
        fileName = filename;

    if(fileName.contains("."))
            fileName.chop(4);
    if(fileName.isEmpty())
        fileName = "unknown_name";

    QString name = fileName.remove(0, fileName.lastIndexOf("/")+1);      //usunięcie folderu - sama nazwa
    QString svgName = name + ".svg";
    QString texName = name + ".tex";
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

  //  stat* st;

    s =     "\\documentclass[11pt,a4paper]{article}\n"
            "\\usepackage{polski}\n"
            "\\usepackage[utf8]{inputenc}\n"
            "\\usepackage{mathtools}\n"
            "\\usepackage{color}\n"
            "\\usepackage{graphicx}\n"
            "\\usepackage{transparent}\n"
            "\\mathtoolsset{showonlyrefs}\n"
            "\\title{Praca inżynierska}\n"
            "\\author{Kamil Strzempowicz}\n"
            "\\date{}\n"
            "\\begin{document}\n"
            "\\maketitle\n"
            "\\begin{abstract}\n"
            "\tStrategia Just in Time w systemach produkcyjnych - analiza struktury gniazdowej dla heurystyk FIFO i LIFO.\n"
            "\\end{abstract}\n"
            "\\section{Tekst}\\label{sec:Wstęp}\n"
            "\tjakiś tekst\n"
            "\t\\begin{figure}[htb]\n"
            "\t\t\\centering\n"
            "\t\t\\def\\svgwidth{\\columnwidth}\n"
            "\t\t\\input{";
    s +=    pdfName + "_tex}\n"
            "\t\t\\caption{Gantt chart}\n"
            "\t\t\\end{figure}\n"
            "\t\\begin{equation}\n"
            "\t\t\\sqrt{(\\sum e_j^2 + \\sum l_j^2} = ";
    s +=    QString::number(w1);
    s +=    "\t\t\\label{eqn:w1}\n"
            "\t\\end{equation}\n"
            "\\end{document}\n";
/*
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
*/


    QFile f(texName);
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream ts(&f);
    ts << s;
    f.close();

    int rc;
    QStringList args;
    QString program("inkscape");

    args << "-z" << "-f" << svgName << "--export-latex" << "--export-pdf" << pdfName << "-D";
    DEBUG << "command: " << program << " args: " << args;
    rc = QProcess::execute(program, args);
    DEBUG << program << " return code: " << rc;

    args.clear();
    args << "--pdf" << texName;
    program = "rubber";
    DEBUG << "command: " << program << " args: " << args;
    rc = QProcess::execute(program, args);
    DEBUG << program << " return code: " << rc;

      /*
    sys = "inkscape -z -f=";
    sys += svgName;
    sys += " --export-latex -E=";
    sys += pdfName;
    sys += " -D";


    rc = system(sys.toAscii());
    DEBUG << "inkscape return code: " << rc;

    sys = "rubber --into=./.. --pdf ";
    sys += texName;
    DEBUG << "command: " << sys;
    rc = system(sys.toAscii());
    DEBUG << "rubber return code: " << rc;
            */
    QDir::setCurrent(cur.path());
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


