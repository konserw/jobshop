#ifndef ZADANIE_H
#define ZADANIE_H

#include <QObject>
#include <QList>
#include "grafZadanie.h"

class Operation;
class Result;


/*!
 * \brief The Job class. Represents one job from jobshop problem
 */
class Job : public QObject
{
    Q_OBJECT

public:
    Job(int number, int start_time, int due_date);
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

    QString print()const;

public slots:
    void update();
    void done();

signals:
    void next(qint32, Job*);
    void finished(Result*);

private:
    int j;
    int rj;
    int dj;

    QList<Operation*> m_operations;

    QColor* m_color;
};

#endif // ZADANIE_H
