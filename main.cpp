#include "MainWindow.h"
#include "Logger.h"

#include <QStringList>
#include <QTextCodec>
#include <QtDebug>
#include <QApplication>

//#define TESTRUN 1

#ifdef TESTRUN
#include "EvolutionWindow.h"
#include "ResultWindow.h"
#include "GanttChart.h"
#include "Jobshop.h"
#include "JobshopModel.h"
#include <QFile>
#include <QDataStream>

void load_sample()
{
    QFile file("sample.mar");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    Jobshop::instance()->model()->loadModel(in);
}

void fifo_lifo()
{
    load_sample();
    Jobshop::instance()->generateInitialPopulation();

    auto a = Jobshop::instance()->fifoChromosome();
    ResultWindow win(a);
    win.save2("/home/konserw/studia/ZZSI/raport/sample/fifo.svg");
    win.latex2("/home/konserw/studia/ZZSI/raport/sample/fifo.tex");

    auto b = Jobshop::instance()->lifoChromosome();
    ResultWindow win2(b);
    win2.save2("/home/konserw/studia/ZZSI/raport/sample/lifo.svg");
    win2.latex2("/home/konserw/studia/ZZSI/raport/sample/lifo.tex");
}

int direct_evo()
{
    load_sample();
    EvolutionWindow evo;
    return evo.exec();
}
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    if(Logger::instance())
        qInstallMessageHandler(Logger::logHandler);
    else
        qDebug() << "Unable to create Logger instance!";

#if TESTRUN == 1
    return direct_evo();
#elif TESTRUN == 2
    fifo_lifo();
    return 0;
#else
    QStringList args = app.arguments();

    MainWindow w;
    if(args.contains("-m") || args.contains("--maximize"))
        w.showMaximized();
    else
        w.show();

    return app.exec();
#endif
}
