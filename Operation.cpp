#include "Operation.h"
#include "Job.h"

Operation::Operation(Job* job, qint32 machine, qint32 time):
    m_job(job), m_machine(machine), m_time(time)
{
}
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
qint32 Operation::machine() const
{
    return m_machine;
}

qint32 Operation::time() const
{
    return m_time;
}

QString Operation::print() const
{
    return QString("%1 (%2)").arg(m_machine).arg(m_time);
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
