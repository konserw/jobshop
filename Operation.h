#ifndef MARSZRUTA_H
#define MARSZRUTA_H

#include <QDataStream>
#include <QString>
#include <QVariant>
class Job;

/*!
 * \brief The Operation class - represents single operation to be executed within a job.
 * Contains information about machine on which it is to be processed and how much time is needed for it to complete.
 */
class Operation
{
public:
    Operation(/*Job* job,*/ qint32 machine = 1, qint32 time = 0);
/* use compiler generated
    ~Operation();
    Operation& operator=(const Operation &in);
*/
    QString print()const;

    QString id() const;
//    void setId(const QString &id);

    qint32 machine() const;
    void setMachine(const qint32 &machine);

    qint32 time() const;
    void setTime(const qint32 &time);

protected:
    /*    Job* m_job;*/
    qint32 m_machine;
    qint32 m_time;
    QString m_id;

    static int m_operationsCount;

    friend QDataStream &operator<<(QDataStream &out, const Operation& op);
    friend QDataStream &operator>>(QDataStream &in, Operation& op);
};

Q_DECLARE_METATYPE(Operation)

QDataStream &operator<<(QDataStream &out, const Operation& op);
QDataStream &operator>>(QDataStream &in, Operation& op);
#endif // MARSZRUTA_H
