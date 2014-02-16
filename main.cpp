#include "MainWindow.h"
#include "Logger.h"

#include <QStringList>
#include <QTextCodec>
#include <QtDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    if(Logger::instance())
        qInstallMessageHandler(Logger::logHandler);
    else
        qDebug() << "Unable to create Logger instance!";

    QStringList args = app.arguments();

    MainWindow w;
    if(args.contains("-m") || args.contains("--maximize"))
        w.showMaximized();
    else
        w.show();

    return app.exec();
}
