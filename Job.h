#ifndef ZADANIE_H
#define ZADANIE_H

#include <QObject>
#include <QList>

class Operation;
class Result;

/*!
 * \brief The Job class. Represents one job from jobshop problem
 */
class Job /* : public QObject
{
    Q_OBJECT
*/
{
public:
    Job(int operationsCount = 0);
    Job(int start_time, int due_date);
    ~Job();

    int number() const;

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
    Operation* operation(int number) const;

    QString print() const;
    void setOperationsCount(int count);

private:
    int m_number;
    QString m_name;
    int m_arrival;
    int m_dueDate;
    double m_alpha;
    double m_beta;

    QList<Operation*> m_operations;

    QColor* m_color;

    static int m_jobsCount;

    friend QDataStream &operator<<(QDataStream &out, const Job & job);
    friend QDataStream &operator>>(QDataStream &in, Job & job);
};

QDataStream &operator<<(QDataStream &out, const Job & job);
QDataStream &operator>>(QDataStream &in, Job & job);

#endif // ZADANIE_H
