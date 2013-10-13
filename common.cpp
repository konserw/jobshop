#include "common.h"
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QTextCodec>
#include <QtDebug>

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
