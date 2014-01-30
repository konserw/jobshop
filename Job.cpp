#include "Job.h"
#include "Operation.h"

#include <QColor>
#include <QtDebug>

int Job::m_jobsCount = 0;

Job::Job(int operationsCount):
    m_arrival(0), m_dueDate(10), m_alpha(0.5), m_beta(0.5)
{
    m_number = ++m_jobsCount;
    m_color =  new QColor(qrand() % 256, qrand() % 256, qrand() % 256);
    setOperationsCount(operationsCount);
}

Job::Job(int start_time, int due_date)
{
    m_number = ++m_jobsCount;
    m_arrival = start_time;
    m_dueDate = due_date;

    m_color =  new QColor(qrand() % 256, qrand() % 256, qrand() % 256);

    qDebug() << "utworzono zadanie nr " << m_number << " rj: " << m_arrival << " dj: " << m_dueDate;
}

Job::~Job()
{
    --m_jobsCount;
    delete m_color;
}

int Job::number() const
{
    return m_number;
}

QString Job::print() const
{
    QString s;
    bool f = false;
    for(const Operation& operation : m_operations)
    {
        if(operation.time() > 0)
        {
            if(f)
                s += " - ";

            s += operation.print();

            if(!f)
                f = true;
        }
    }
    return s;
}

void Job::setOperation(int number, const Operation &operation)
{
    //TODO zmiana z pointerow na normalne itemy
    m_operations[number] = operation;
}

const Operation& Job::operation(int number) const
{
    if(number < m_operations.count())
        return m_operations[number];
    qWarning() << "requested invalid operation";
    return Operation();
}

void Job::setOperationsCount(int count)
{
    for(int i = m_operations.count()-1; i >= count; --i)
    {
        m_operations.removeAt(i);
    }
    for(int i = m_operations.count(); i < count; ++i)
    {
        m_operations.append(Operation());
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
