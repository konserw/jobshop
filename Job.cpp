#include "Job.h"
#include "Operation.h"
#include "Jobshop.h"

#include <QColor>
#include <QtDebug>

int Job::m_jobsCount = 0;

Job::Job(int operationsCount):
    m_arrival(0), m_dueDate(10), m_alpha(0.5), m_beta(0.5)
{
    m_id = 'A' + m_jobsCount++;
    m_color =  new QColor(qrand() % 256, qrand() % 256, qrand() % 256);
    setOperationsCount(operationsCount);
}

Job::Job(int start_time, int due_date)
{
    m_id = 'A' + m_jobsCount++;
    m_arrival = start_time;
    m_dueDate = due_date;

    m_color =  new QColor(qrand() % 256, qrand() % 256, qrand() % 256);
}

Job::~Job()
{
    m_jobsCount;
    delete m_color;
}

QString Job::print() const
{
    QString s;
    bool f = false;
    for(const QString& id : m_operationIds)
    {
        const Operation& operation = Jobshop::instance()->operation(id);
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
    Jobshop::instance()->operation(operationId(number)) = operation;
    //m_operations[number] = operation;
}

Operation& Job::operation(int number)
{
    return Jobshop::instance()->operation(operationId(number));
}

const Operation& Job::operation(int number) const
{
    return Jobshop::instance()->operation(operationId(number));
}

void Job::setOperationsCount(int count)
{
    for(int i = m_operationIds.count()-1; i >= count; --i)
    {
        QString id = operationId(i);
        m_operationIds.removeOne(id);
        Jobshop::instance()->removeOperation(id);
    }
    for(int i = m_operationIds.count(); i < count; ++i)
    {
        m_operationIds.append(Jobshop::instance()->operation(operationId(i)).id());
    }
}

QString Job::id() const
{
    return m_id;
}

QString Job::operationId(int number) const
{
    return QString("%1%2").arg(m_id).arg(number);
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
