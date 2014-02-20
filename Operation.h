#ifndef MARSZRUTA_H
#define MARSZRUTA_H

#include <QDataStream>
#include <QString>
#include <QVariant>

class GanttOperation;
class Job;

/*!
 * \brief The Operation class - represents single operation to be executed within a job.
 * Contains information about machine on which it is to be processed and how much time is needed for it to complete.
 */
class Operation
{
public:
    Operation();
    Operation(const QString &id, int machine = 0, int time = 0);

    bool operator==(const Operation& other);

    Operation& operator=(const Operation& other);
    Operation(const Operation& other);

    QString print()const;

    QString id() const;

    int machine() const;
    void setMachine(int machine);

    int time() const;
    void setTime(int time);

    int jobNumber() const;

    GanttOperation* ganttGraphic() const;

    bool isValid() const;

protected:
    QString m_id;
    int m_machine;
    int m_time;
    GanttOperation* m_graphic;
    bool m_valid;

    friend QDataStream &operator<<(QDataStream &out, const Operation& op);
    friend QDataStream &operator>>(QDataStream &in, Operation& op);
};

Q_DECLARE_METATYPE(Operation)

QDataStream &operator<<(QDataStream &out, const Operation& op);
QDataStream &operator>>(QDataStream &in, Operation& op);

QDebug& operator<< (QDebug& d, const Operation& operation);

#endif // MARSZRUTA_H
