#ifndef ZADANIE_H
#define ZADANIE_H

#include <QObject>
#include <QList>

class Operation;
class Result;


/*!
 * \brief The Job class. Represents one job from jobshop problem
 */
class Job : public QObject
{
    Q_OBJECT

public:
    Job();
    Job(int start_time, int due_date);
    ~Job();

    int number()const
    {
        return j;
    }

    int due() const
    {
        return dj;
    }

    int arrive() const
    {
        return rj;
    }

    QString print() const;
    QVariant data(int col) const;

private:
    int j;
    QString m_name;
    int rj;
    int dj;
    double m_alpha;
    double m_beta;

    QList<Operation*> m_operations;

    QColor* m_color;

    static int jobsCount;
};

#endif // ZADANIE_H
