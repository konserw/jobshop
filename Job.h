#ifndef ZADANIE_H
#define ZADANIE_H

#include <QObject>
#include <QList>

class Operation;
class Result;
class QModelIndex;

/*!
 * \brief The Job class. Represents one job from jobshop problem
 */
class Job : public QObject
{
    Q_OBJECT

public:
    Job(int operationsCount = 0);
    Job(int start_time, int due_date);
    ~Job();

    int number()const
    {
        return j;
    }

    QString print() const;
    QVariant data(const QModelIndex &index, int role) const;

    void setOperation(int number, const Operation& operation);
    Operation* operation(int number) const;
    void setOperationsCount(int count);

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

private:
    int j;
    QString m_name;
    int m_arrival;
    int m_dueDate;
    double m_alpha;
    double m_beta;

    QList<Operation*> m_operations;

    QColor* m_color;

    static int jobsCount;

    friend QDataStream &operator<<(QDataStream &out, const Job & job);
    friend QDataStream &operator>>(QDataStream &in, Job & job);
};

QDataStream &operator<<(QDataStream &out, const Job & job);
QDataStream &operator>>(QDataStream &in, Job & job);

#endif // ZADANIE_H
