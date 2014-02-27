#include "ResultWindow.h"
#include "ui_ResultWindow.h"
#include "Job.h"
#include "Result.h"
#include "Jobshop.h"
#include "ResultsModel.h"

#include <QDebug>
#include <QtWidgets>
#include <QFileDialog>
#include <QtAlgorithms>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QTextCodec>
#include <QtDebug>
#include <QtSvg/QSvgGenerator>

int run(const QString &program, const QStringList &args)
{
    int rc;
    qDebug() << "running command: " << program << " args: " << args;
    rc = QProcess::execute(program, args);
    qDebug() << program << " returned code: " << rc;
    return rc;
}

void save(const QString &fileName, const QString &content)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream ts(&file);
    ts.setCodec(QTextCodec::codecForName("UTF-8"));
    ts << content;
    file.close();
}

ResultWindow::ResultWindow(const Chromosome& chromosome, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultWindow),
    m_chromosome(chromosome)
{
    ui->setupUi(this);

    setWindowModality(Qt::ApplicationModal);

    //Podsumowanie obliczeń
    //Eksport LaTeXu

    //per job stats
    ui->tableView->setModel(new ResultsModel(chromosome.results(), this));
    ui->tableView->resizeColumnsToContents();
    //global stats
    ui->label->setTextFormat(Qt::RichText);
    ui->label->setStyleSheet("QLabel { vertical-align: middle; font-size: 12pt; background-color: white; color: black; }");
    ui->label->setText(QString(
                           "Completion Time = %1<br />\n"
                           "Mean Flow Time = %2<br />\n"
                           "Number of tardy jodbs = %3 <br />\n"
                           "Maximum tardiness = %4<br />\n"
                           "Mean tardiness = %5<br />\n"
                           "<img src=:/w1> %6<br />\n"
                           "<img src=:/w2> %7<br />\n"
                           )
                       .arg(m_chromosome.completionTime())
                       .arg(m_chromosome.meanFlow())
                       .arg(m_chromosome.tardy())
                       .arg(m_chromosome.maxTardy())
                       .arg(m_chromosome.meanTardy())
                       .arg(m_chromosome.valueMean())
                       .arg(m_chromosome.valueAlpha())
                       );

    m_chart = m_chromosome.ganttChart();

    m_scene = new QGraphicsScene(this);
    m_scene->addItem(m_chart);

    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    connect(ui->pushButton_latex, &QPushButton::clicked, this, &ResultWindow::latex);
    connect(ui->pushButton_save, &QPushButton::clicked, this, &ResultWindow::saveChart);
}

ResultWindow::~ResultWindow()
{
    delete ui;
}

void ResultWindow::changeEvent(QEvent *e)
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

/*
void ResultWindow::pdf()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Export wyników do pliku PDF"), "", tr("Plik PDF (*.pdf)"));
    if(fileName.isEmpty())return;

    this->pdf(fileName);
}
*/
void ResultWindow::latex()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Export wyników do LaTeXu"), "", tr("Plik tex (*.tex)"));
    if(fileName.isEmpty())return;
    this->latex2(fileName);
}

void ResultWindow::latex2(const QString &texName)
{
    /*
    QFileInfo fi(texName);
    const QString svgName(QString("%2/gantt_%1.svg").arg(fi.baseName()).arg(fi.absolutePath()));

    save2(svgName);
*/
    QString s;
    s = Jobshop::instance()->latexSummary();
    s += m_chromosome.latexSummary();
    save(texName, s);
}

void ResultWindow::saveChart()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Export chart to file"), "", tr("Scalable Vector Graphics (*.svg)"));
    if(fileName.isEmpty())return;
    this->save2(fileName);
}

void ResultWindow::save2(const QString &filename)
{
    QSvgGenerator svgGen;
    svgGen.setFileName(filename);
    QRectF r = m_scene->sceneRect();
    r.moveTopLeft(QPointF(0,0));
    qDebug() << "image size:" << r << r.size().toSize();
    svgGen.setSize(r.size().toSize());
    svgGen.setViewBox(r);
    svgGen.setTitle(tr("Gantt chart"));
    svgGen.setDescription(tr("Gantt chart"));
    QPainter painter;
    painter.begin(&svgGen);
    m_scene->render(&painter);
    painter.end();
}
