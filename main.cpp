#include <QtGui/QApplication>
#include "MainWindow.h"
#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QStringList* args = new QStringList(app.arguments());
    bool cli = (args->count() > 1);
    if(cli)
    {
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
        if(!args->contains(".mar") && !(args->contains("-l") || args->contains("--list")))
        {
            qDebug() << "Nothing to process";
            qDebug() << "See 'kSzereg --help'' for more information.";
            return 0;
        }
    }

    MainWindow w(args);
    if(!cli) w.show();
    return app.exec();
}
