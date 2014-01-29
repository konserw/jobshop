#include "Job.h"
#include "Operation.h"

#include <QModelIndex>
#include <QColor>
#include <QtDebug>

int Job::jobsCount = 0;

Job::Job(int operationsCount):
    m_arrival(0), m_dueDate(0), m_alpha(0), m_beta(0)
{
    j = ++jobsCount;
    m_color =  new QColor(qrand() % 256, qrand() % 256, qrand() % 256);
    setOperationsCount(operationsCount);
}

Job::Job(int start_time, int due_date)
{
    j = ++jobsCount;
    m_arrival = start_time;
    m_dueDate = due_date;

    m_color =  new QColor(qrand() % 256, qrand() % 256, qrand() % 256);

    qDebug() << "utworzono zadanie nr " << j << " rj: " << m_arrival << " dj: " << m_dueDate;
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

QVariant Job::data(const QModelIndex &index, int role) const
{
    int column = index.column();
    switch(column)
    {
    case 0:
        return m_name;
    case 1:
        return m_arrival;
    case 2:
        return m_dueDate;
    case 3:
        return m_alpha;
    case 4:
        return m_beta;
    default:
        if(role == Qt::EditRole)
            return QVariant::fromValue(*m_operations[column-5]);
        return m_operations[column-5]->print();
    }
}

void Job::setOperation(int number, const Operation &operation)
{
    //TODO zmiana z pointerow na normalne itemy
    m_operations[number] = new Operation(operation);
}

Operation *Job::operation(int number) const
{
    if(number < m_operations.count())
        return m_operations[number];
    return nullptr;
}

void Job::setOperationsCount(int count)
{
    for(int i = m_operations.count()-1; i >= count; --i)
    {
        delete m_operations[i];
        m_operations.removeAt(i);
    }
    for(int i = m_operations.count(); i < count; ++i)
    {
        m_operations.append(new Operation());
    }
}

QString Job::name() const
{
    return m_name;
}

void Job::setName(const QString &name)
{
    m_name = name;
}

double Job::alpha() const
{
    return m_alpha;
}

void Job::setAlpha(double alpha)
{
    m_alpha = alpha;
}
double Job::beta() const
{
    return m_beta;
}

void Job::setBeta(double beta)
{
    m_beta = beta;
}
int Job::arrival() const
{
    return m_arrival;
}

void Job::setArrival(int arrival)
{
    m_arrival = arrival;
}
int Job::dueDate() const
{
    return m_dueDate;
}

void Job::setDueDate(int dueDate)
{
    m_dueDate = dueDate;
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
