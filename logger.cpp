#include "logger.h"
#include <QDate>
#include <QDebug>
#include <QTextStream>
#include <iostream>
#include <QFile>
#include <QString>
#include <QCoreApplication>
#include <QDir>

Logger* Logger::m_instance = NULL;

void Logger::logOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString debugInfo;

    if(type == QtDebugMsg)
        debugInfo = QString("[%1]:\t").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
    else
        debugInfo = QString("[%2:%3][%1]:\t").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")).arg(context.function).arg(context.line);


    if(m_out)
        (*m_out) << debugInfo << msg << endl;
    else
        std::cerr << debugInfo.toStdString() << msg.toStdString() << std::endl;

#ifdef CONSOLE_OUT
    std::cout << msg.toStdString() << std::endl;
#endif

    if(type == QtFatalMsg)
    {
        abort();
    }
}

Logger::Logger()
{
    m_out = nullptr;
    m_log = nullptr;
    setFilePath(filePath(".log"));
}

Logger::~Logger()
{
    delete m_out;
    delete m_log;
}

QString Logger::filePath(const char *suffix)
{
    QString path = QCoreApplication::applicationFilePath();
#ifdef WIN32
    path = path.replace(".exe", suffix);
#else
    path = path + suffix;
#endif
    return QDir::toNativeSeparators(path);
}

Logger *Logger::instance()
{
    if(m_instance == NULL)
        m_instance = new Logger;

    return m_instance;
}

void Logger::logHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Logger::instance()->logOutput(type, context, msg);
}

bool Logger::setFilePath(const QString &path)
{
    delete m_out;
    delete m_log;

    m_log = new QFile(path);
    if(!m_log->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Error opening log file '" << path << "'. All debug output redirected to console.";
        delete m_log;
        m_log = nullptr;
        m_out = nullptr;
        return false;
    }

    m_out = new QTextStream(m_log);
    (*m_out) << "=========================================================================================\n";

    return true;
}
