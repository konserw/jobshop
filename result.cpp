#include "Result.h"
#include <cmath>

Result::Result(const QString &jobID, int completionTime, int dueDate, int arrivalDate)
{
    m_jobID = jobID;
    m_flow = completionTime - arrivalDate;
    m_completionTime = completionTime;

    m_lateness = completionTime - dueDate;
    m_earliness = 0;

    if(m_lateness < 0)
    {
        m_earliness = std::abs(m_lateness);
        m_lateness = 0;
    }
}

bool Result::operator<(const Result other) const
{
    return m_jobID < other.jobID();
}

bool Result::operator>(const Result other) const
{
    return m_jobID < other.jobID();
}

int Result::flow() const
{
    return m_flow;
}

int Result::completionTime() const
{
    return m_completionTime;
}

int Result::lateness() const
{
    return m_lateness;
}

int Result::earliness() const
{
    return m_earliness;
}

QString Result::jobID() const
{
    return m_jobID;
}
