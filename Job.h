#ifndef ZADANIE_H
#define ZADANIE_H

#include "Operation.h"

#include <QList>
#include <QColor>

/*!
 * \brief The Job class. Represents one job from jobshop problem
 */
class Job
{
public:
    Job(int operationsCount = 0, int start_time = 0, int due_date = 10);
    Job(const Job& other);
    ~Job();

    QString name() const;
    void setName(const QString &name);

    double alpha() const;
    void setAlpha(double alpha);

    double beta() const;
    void setBeta(double beta);

    int arrival() const;
    void setArrival(int arrival);

    int dueDate() const;
    void setDueDate(int dueDate);

    void setOperation(int number, const Operation& operation);
    const Operation &operation(int number) const;
    Operation &operation(int number);

    QString print() const;
    void setOperationsCount(int count);

    QString id() const;
    int totalTime() const;

    const QColor& color() const;

    QString printCompact() const;

private:
    QString m_id;
    QString m_name;
    int m_arrival;
    int m_dueDate;
    double m_alpha;
    double m_beta;

    QList<QString> m_operationIds;
    QString operationId(int number) const;

    QColor m_color;

    static int m_jobsCount;

    friend QDataStream &operator<<(QDataStream &out, const Job & job);
    friend QDataStream &operator>>(QDataStream &in, Job & job);
    friend QDebug& operator<< (QDebug& d, const Job& job);
    friend class Jobshop;
};

QDataStream &operator<<(QDataStream &out, const Job & job);
QDataStream &operator>>(QDataStream &in, Job & job);

QDebug& operator<< (QDebug& d, const Job& job);

#endif // ZADANIE_H
