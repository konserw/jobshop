#include "maszyna.h"
#include <QtGui/QApplication>
#include "MainWindow.h"
#include <QTextCodec>
#include "common.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

//global extern variables
bool cli;
qint32 t=0;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QStringList* files;
    QStringList* args = new QStringList(app.arguments());

    cli = (args->count() > 1);
    //GUI operation
    if(!cli)
    {
        MainWindow w;
        w.show();
        delete args;
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
        qDebug() << "\t-h, --heuristic <type>\tSet heuristic used to resolve conflicts. FIFO is default";
        qDebug() << "\t-l, --list <list>\tImport list of .mar files to process from <list>";
        qDebug() << "\t<file> [...]\t\tFiles to process. <file> have to be file exported from kSzereg in the .mar format";
        qDebug() << "";
        qDebug() << "Aviable heuristics:";
        qDebug() << "\tFIFO\t\t\tFirst In First Out";
        qDebug() << "\tLIFO\t\t\tLast In First Out";
        delete args;
        return 0;
    }

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

        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString s = in.readLine();
            if(!s.isEmpty())
                files->append(s);
        }
        DEBUG << "wczytano liste plikow.";
        DEBUG << *files;
    }

    if(args->contains("-h") || args->contains("--heuristic"))
    {
        int where = args->indexOf("-h");
        if(where == -1)
            where = args->indexOf("--heuristic");
        ++where;

        if(args->count() < where+1)
        {
            qDebug() << "You have to specify name of list heuristic after -h option (ater white char)";
            qDebug() << "See 'kSzereg --help'' for more information.";
            return 1;
        }
        if(args->at(where) == "FIFO")
            maszyna::method = 0;
        else if(args->at(where) == "LIFO")
            maszyna::method = 1;
        else
        {
            qDebug() << "Only FIFO and LIFO heuristics are aviable atm.";
            qDebug() << "See 'kSzereg --help'' for more information.";
            return 1;
        }
    }
    else
        maszyna::method = 0; //defaults to FIFO

    DEBUG << "wybrana heurystyka: " << maszyna::method;

    for(int i=0; i<files->count(); ++i)
    {
        MainWindow w(files->at(i));
    }

    delete args;
    delete files;
    return 0;
}
