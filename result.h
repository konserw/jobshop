#ifndef RESULT_H
#define RESULT_H

#include <QString>

class Result
{
public:
    Result(const QString& jobID, int completionTime, int dueDate, int arrivalDate);

    //operators for sorting purposes
    bool operator<(const Result other) const;
    bool operator>(const Result other) const;

    //getters
    QString jobID() const;
    int flow() const;
    int completionTime() const;
    int lateness() const;
    int earliness() const;


private:
    QString m_jobID;
    int m_flow;
    int m_completionTime;
    int m_lateness;
    int m_earliness;
};

bool comparecompletionTime(const Result& a, const Result& b);

#endif // RESULT_H
