//#include "maszyna.h"
#include "MainWindow.h"
#include "logger.h"
#include "common.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTextCodec>
#include <QtDebug>
#include <QApplication>
#include <iostream>
using std::cout;

//global extern variables
bool cli;
int t = 0;
int fmt = 0;
double rot = 0;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

#ifndef QT_NO_DEBUG_OUTPUT
    if(Logger::instance())
        qInstallMessageHandler(Logger::logHandler);
    else
        qDebug() << "Unable to create Logger instance!";
#endif

    QStringList* files;
    QStringList* args = new QStringList(app.arguments());

    bool m = false;
    cli = (args->count() > 1);
    if(cli && (args->contains("-m") || args->contains("--maximize")))
    {
        cli = false;
        m = true;
    }
    //GUI operation
    if(!cli)
    {
        MainWindow w;
        if(m)
            w.showMaximized();
        else
            w.show();
        delete args;
        return app.exec();
    }

    //display cli help text
    if(args->contains("--help", Qt::CaseInsensitive) || args->contains("-h", Qt::CaseInsensitive))
    {
        cout << "usage: jobshop [-l <list>] [-p] [-m] [-r] [--help]\n"; //[<file> ...] ";
        cout << "or jobshop without arguments for GUI operation\n";
        cout << "Strategy Just in Time in manufacturing systems - FIFO and LIFO heuristics analysis\n";
        cout << "for job shop problem.\n\n";

        cout << "OPTIONS:\n";
        cout << "\t--help\t\t\tDisplay this help text and exit\n";
        cout << "\t-m, --maximize\t\tGUI operation with maximized window\n";
        cout << "\t-l, --list <list>\tImport list of .mar files to process from <list>\n";
      //  qDebug() << "\t<file> [...]\t\tFiles to process. <file> have to be file exported from kSzereg in the .mar format";
        cout << "\t-p, --pdf\t\tCompile LaTeX output to .pdf format\n";
        cout << "\t-r, --rotate <deg>\tRotate Gantt chart by <deg> degrees clockwise, default 0\n\n" << std::endl;

        delete args;
        return 0;
    }

    if(args->contains("-p") || args->contains("--pdf"))
        fmt = 1;

    files = new QStringList;

    if(args->contains("-l") || args->contains("--list"))
    {
        int where = args->indexOf("-l");
        if(where == -1)
            where = args->indexOf("--list");
        ++where;

        if(args->count() < where+1)
        {
            qDebug() << "You have to specify name of list file after -l option (ater white char)";
            qDebug() << "See 'kSzereg --help'' for more information.";
            return 1;
        }
        QString fileName = args->at(where);
        qDebug() << "wykryto -l, otwieranie pliku listy: " << fileName;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Error occured while openning list file";
            if(!file.exists())qDebug() << "File '" << fileName << "' does not exist.";
            else qDebug() << "File '" << fileName << "' is not aviable.";
            return 1;
        }
        qDebug() << "Otworzono plik listy";

        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString s = in.readLine();
            if(!s.isEmpty())
                files->append(s);
        }
        qDebug() << "wczytano liste plikow.";
        qDebug() << *files;
    }

    if(args->contains("-r") || args->contains("--rotate"))
    {
        int where = args->indexOf("-r");
        if(where == -1)
            where = args->indexOf("--rotate");
        ++where;

        if(args->count() < where+1)
        {
            cout << "You have to specify <deg> after -r option (ater white char)";
            cout << "See 'kSzereg --help'' for more information.";
            return 1;
        }

        rot = args->at(where).toDouble();
    }

    /*
      Koniec przetwarzania argumentów
      */

    for(int i=0; i<files->count(); ++i)
    {
            MainWindow w(files->at(i));
    }

    delete args;
    delete files;
    return 0;
}
