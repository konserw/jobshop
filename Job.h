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

    int time();
    void add_rout(Operation*);

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

    QGraphicsItem* gItem();
signals:
    void next(qint32, Job*);
    void finished(Result*);
private:
    int j;
    int rj;
    int dj;
    int cur;
    QList<Operation*> rout;
    bool blocked;

    QList<grafZadanie*> grafiki;
    QColor* col;
};

#endif // ZADANIE_H
