#include <QtGui/QApplication>
#include "MainWindow.h"
#include <QTextCodec>
#include "common.h"
#include <QFile>
#include <QTextStream>

//global extern variables
bool cli;
qint32 t=0;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QStringList* files;
    QStringList* args = new QStringList(app.arguments());
    *args << "-l";
    cli = (args->count() > 1);

    //GUI operation
    if(!cli)
    {
        MainWindow w;
        w.show();
        return app.exec();
    }

    //display cli help text
    if(args->contains("--help", Qt::CaseInsensitive))
    {
        qDebug() << "usage: kSzereg [-h <heuristics>] [-l <list>] [<file> ...]";
        qDebug() << "or kSzereg without arguments for GUI operation";
        qDebug() << "Strategy Just in Time in manufacturing systems - FIFO and LIFO heuristics analysis";
        qDebug() << "for job shop problem.";
        qDebug() << "";
        qDebug() << "OPTIONS:";
        qDebug() << "\t--help\t\t\tDisplay this help text and exit";
        qDebug() << "\t-h, --heuristics <type>\tSet heuristics used to resolve conflicts. FIFO is default";
        qDebug() << "\t-l, --list <list>\tImport list of .mar files to process from <list>";
        qDebug() << "\t<file> [...]\t\tFiles to process. <file> have to be file exported from kSzereg in the .mar format";
        qDebug() << "";
        qDebug() << "Aviable heuristics:";
        qDebug() << "\tFIFO\t\t\tFirst In First Out";
        qDebug() << "\tLIFO\t\t\tLast In First Out";
        return 0;
    }
    if(args->contains("-l") || args->contains("--list"))
    {
        int where = args->indexOf("-l");
        if(where == -1)
            where = args->indexOf("--list");
        ++where;

        if(args->count() < where)
        {
            qDebug() << "You have to specify name of list file after -l option";
            qDebug() << "See 'kSzereg --help'' for more information.";
            return 1;
        }
        QString fileName = args->at(where);
        DEBUG << "wykryto -l, otwieranie pliku listy: " << fileName;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Error occured while openning list file";
            if(!file.exists())DEBUG << "File '" << fileName << "' does not exist.";
            else DEBUG << "File '" << fileName << "' is not aviable.";
            return 1;
        }
        DEBUG << "Otworzono plik listy";
        files = new QStringList;
        QTextStream in(&file);
        while(!in.atEnd())
            files->append(in.readLine());
        DEBUG << "wczytano liste plikow.";
        DEBUG << *files;
    }
/*
   {
        qDebug() << "Nothing to process";
        qDebug() << "See 'kSzereg --help'' for more information.";
        return 0;
    }
    */
}
