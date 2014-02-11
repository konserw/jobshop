#include "Result.h"
#include <cmath>

Result::Result(int number, int completionTime, int dueDate, int arrivalDate)
{
    m_number = number;
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
    return this->number() < other.number();
}

bool Result::operator>(const Result other) const
{
    return this->number() > other.number();
}

int Result::number() const
{
    return m_number;
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

bool comparecompletionTime(const Result& a, const Result& b)
{
    return a.completionTime() < b.completionTime();
}
