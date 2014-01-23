#ifndef MARSZRUTA_H
#define MARSZRUTA_H

#include <QDataStream>
#include <QString>
class Job;

/*!
 * \brief The Operation class - represents single operation to be executed within a job.
 * Contains information about machine on which it is to be processed and how much time is needed for it to complete.
 */
class Operation
{
public:
    Operation(Job* job, qint32 machine = 1, qint32 time = 0);
/* use compiler generated
    ~Operation();
    Operation& operator=(const Operation &in);
*/
    qint32 machine()const;
    qint32 time()const;

    QString print()const;

protected:
    Job* m_job;
    qint32 m_machine;
    qint32 m_time;

    friend QDataStream &operator<<(QDataStream &out, const Operation& op);
    friend QDataStream &operator>>(QDataStream &in, Operation& op);
};

QDataStream &operator<<(QDataStream &out, const Operation& op);
QDataStream &operator>>(QDataStream &in, Operation& op);
#endif // MARSZRUTA_H
