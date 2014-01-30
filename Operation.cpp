#include "Operation.h"
#include "Job.h"

//#include <QSize>

const int PaintingScaleFactor = 80;
int Operation::m_operationsCount = 0;

Operation::Operation(/*Job* job,*/ qint32 machine, qint32 time):
   /* m_job(job),*/ m_machine(machine), m_time(time)
{
    QChar first = 'A' + m_operationsCount/10;
    m_id = QString("%1%2").arg(first).arg(m_operationsCount%10);
    m_operationsCount++;
}
/*
QSize Operation::sizeHint() const
{
    return PaintingScaleFactor * QSize(3, 2);
}
*/
/*
Operation::~Operation()
{
}
Operation &Operation::operator =(const Operation &in)
{
    if(this != &in)
    {
        m_time = in.m_time;
        m_job = in.m_job;
        m_machine = in.m_machine;
    }

    return *this;
}
*/

QString Operation::print() const
{
    return QString("Operation %1:\n%2h on machine %3").arg(m_id).arg(m_time).arg(m_machine+1);
}

QString Operation::id() const
{
    return m_id;
}

/*
void Operation::setId(const QString &id)
{
    m_id = id;
}
*/

qint32 Operation::machine() const
{
    return m_machine;
}

void Operation::setMachine(const qint32 &machine)
{
    m_machine = machine;
}

qint32 Operation::time() const
{
    return m_time;
}

void Operation::setTime(const qint32 &time)
{
    m_time = time;
}

QDataStream &operator<<(QDataStream &out, const Operation &op)
{
    out << op.m_machine
        << op.m_time;
    return out;
}

QDataStream &operator>>(QDataStream &in, Operation &op)
{
    in >> op.m_machine
       >> op.m_time;
    return in;
}
