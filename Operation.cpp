#include "Operation.h"
#include "Job.h"
#include "GanttOperation.h"
#include "Jobshop.h"
#include <QtDebug>

Operation::Operation()
{
    m_time = 0;
    m_valid = false;
}

Operation::Operation(const QString& id, int machine, int time) :
    m_id(id),
    m_machine(machine),
    m_time(time),
    m_valid(true)
{
}

bool Operation::operator==(const Operation &other)
{
    return other.m_id == m_id;
}

Operation &Operation::operator=(const Operation &other)
{
    m_id = other.m_id;
    m_machine = other.m_machine;
    m_time = other.m_time;
    m_valid = other.m_valid;

    return *this;
}

Operation::Operation(const Operation &other)
{
    m_id = other.m_id;
    m_machine = other.m_machine;
    m_time = other.m_time;
    m_valid = other.m_valid;
}

QString Operation::print() const
{
    if(m_time)
        return QString("Operation %1:\n%2h on machine %3").arg(m_id).arg(m_time).arg(m_machine+1);
    return QString();
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

int Operation::jobNumber() const
{
    return m_id[0].toLatin1() - 'A';
}

GanttOperation *Operation::ganttGraphic() const
{
    return new GanttOperation(m_id, m_time, Jobshop::instance()->jobs()[this->jobNumber()].color());
}

bool Operation::isValid() const
{
    return m_valid;
}

QDataStream &operator<<(QDataStream &out, const Operation &op)
{
    qint64 machine = qint64(op.m_machine);
    qint64 time = qint64(op.m_time);

    out << op.m_id
        << machine
        << time
        << op.m_valid;

    return out;
}

QDataStream &operator>>(QDataStream &in, Operation &op)
{
    qint64 machine;
    qint64 time;

    in  >> op.m_id
        >> machine
        >> time
        >> op.m_valid;

    op.m_machine = machine;
    op.m_time = time;

    op.m_graphic = new GanttOperation(op.m_id, time, Jobshop::instance()->jobs()[op.jobNumber()].color());

    return in;
}


QDebug &operator<<(QDebug &d, const Operation &operation)
{
    d.nospace() << "Operation " << operation.id() << ": " << operation.time() << "h on machine " << operation.machine()+1;
    return d.space();
}
