#include "Job.h"
#include "Operation.h"

#include <QColor>
#include <QtDebug>

int Job::jobsCount = 0;

Job::Job():
    rj(0), dj(0)
{
    j = ++jobsCount;
    m_color =  new QColor(qrand() % 256, qrand() % 256, qrand() % 256);
}

Job::Job(int start_time, int due_date)
{
    j = ++jobsCount;
    rj = start_time;
    dj = due_date;

    m_color =  new QColor(qrand() % 256, qrand() % 256, qrand() % 256);

    qDebug() << "utworzono zadanie nr " << j << " rj: " << rj << " dj: " << dj;
}

Job::~Job()
{
    --jobsCount;
    delete m_color;
}

QString Job::print() const
{
    QString s;
    Operation* m;
    bool f = false;
    foreach(m, m_operations)
    {
        if(m->time() > 0)
        {
            if(f)
                s += " - ";

            s += m->print();

            if(!f)
                f = true;
        }
    }
    return s;
}

QVariant Job::data(int col) const
{
    switch(col)
    {
    case 0:
        return m_name;
    case 1:
        return rj;
    case 2:
        return dj;
    case 3:
        return m_alpha;
    case 4:
        return m_beta;
    default:
        return m_operations[col-4]->print();

    }
}


QDataStream &operator <<(QDataStream &out, const Job &job)
{
    //todo
    return out;
}


QDataStream &operator >>(QDataStream &in, Job &job)
{
    //todo
    return in;
}
