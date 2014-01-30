#include "Operation.h"
#include "Job.h"

Operation::Operation(const QString& id, int machine, int time)
    : m_id(id),
      m_machine(machine),
      m_time(time)
{
}

bool Operation::operator==(const Operation &other)
{
    return other.m_id == m_id;
}

QString Operation::print() const
{
    return QString("Operation %1:\n%2h on machine %3").arg(m_id).arg(m_time).arg(m_machine+1);
}

QString Operation::id() const
{
    return m_id;
}

int Operation::machine() const
{
    return m_machine;
}

void Operation::setMachine(int machine)
{
    m_machine = machine;
}

int Operation::time() const
{
    return m_time;
}

void Operation::setTime(int time)
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
