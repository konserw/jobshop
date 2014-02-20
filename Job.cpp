#include "Job.h"
#include "Operation.h"
#include "Jobshop.h"

#include <QtDebug>

int Job::m_jobsCount = 0;

Job::Job(int operationsCount, int start_time, int due_date) :
    m_arrival(start_time),
    m_dueDate(due_date),
    m_alpha(0.5),
    m_beta(0.5),
    m_color(QColor(qrand() % 256, qrand() % 256, qrand() % 256))
{
    m_id = 'A' + m_jobsCount++;

    if(operationsCount)
        setOperationsCount(operationsCount);
}

Job::Job(const Job &other) :
    m_arrival(other.m_arrival),
    m_dueDate(other.m_dueDate),
    m_alpha(other.m_alpha),
    m_beta(other.m_beta),
    m_color(other.m_color),
    m_id(other.m_id),
    m_operationIds(other.m_operationIds),
    m_name(other.m_name)
{
    ++m_jobsCount;
}



Job::~Job()
{
    for(const QString& id : m_operationIds)
        Jobshop::instance()->removeOperation(id);
    --m_jobsCount;
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

            s += operation.print().replace("\n", " ");

            if(!f)
                f = true;
        }
    }
    return s;
}

QString Job::printCompact() const
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

            s += QString("m%1(%2)")
                    .arg(operation.machine())
                    .arg(operation.time());

            if(!f)
                f = true;
        }
    }
    return s;
}

void Job::setOperation(int number, const Operation &operation)
{
    Jobshop::instance()->operation(operationId(number)) = operation;
}

Operation& Job::operation(int number)
{
    if(number < m_operationIds.count())
        return Jobshop::instance()->operation(operationId(number));

    qWarning() << "requested non existan operation number" << number << "from job" << m_id;
    return Operation();
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
        QString id = operationId(i);
        m_operationIds.append(id);
        Jobshop::instance()->operation(id);
    }
}

QString Job::id() const
{
    return m_id;
}

int Job::totalTime() const
{
    int t = m_arrival;
    for(const QString& op : m_operationIds)
        t += Jobshop::instance()->operation(op).time();
    return t;
}

const QColor &Job::color() const
{
    return m_color;
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
    qint64 count = job.m_operationIds.count();

    out
        << job.m_id
        << job.m_name
        << qint64(job.m_arrival)
        << qint64(job.m_dueDate)
        << qreal(job.m_alpha)
        << qreal(job.m_beta)
        << count;

    for(int i=0; i < count; ++i)
        out << job.m_operationIds[i];

    return out;
}

QDataStream &operator >>(QDataStream &in, Job &job)
{
    qint64 arr, dd, count;
    qreal a, b;

    in
        >> job.m_id
        >> job.m_name
        >> arr
        >> dd
        >> a
        >> b
        >> count;

    job.m_arrival = arr;
    job.m_dueDate = dd;
    job.m_alpha = a;
    job.m_beta = b;

    for(qint64 i=0; i < count; ++i)
    {
        QString id;
        in >> id;
        job.m_operationIds.append(id);
    }

    return in;
}


QDebug& operator<<(QDebug& d, const Job &job)
{

    d << "Arrival:" << job.m_arrival;
    d << "Due date:" << job.m_dueDate;
    d << "Alpha:" << job.m_alpha;
    d << "Beta:" << job.beta();
    d << "Operations:";

    bool f = false;
    for(const QString& id : job.m_operationIds)
    {
        const Operation& operation = Jobshop::instance()->operation(id);
        if(operation.time() > 0)
        {
            if(f)
                d << "-";

            d << operation;

            if(!f)
                f = true;
        }
    }

    return d;
}
