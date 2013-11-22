#include "Job.h"
#include "Operation.h"
#include "common.h"
#include "result.h"
#include <QtDebug>

Job::Job(int number, int start_time, int due_date)
{
    j = number;
    rj = start_time;
    dj = due_date;

    cur=0;
    blocked = false;

    col =  new QColor(qrand() % 256, qrand() % 256, qrand() % 256);

    qDebug() << "utworzono zadanie nr " << j << " rj: " << rj << " dj: " << dj;
}

Job::~Job()
{
    delete col;
}

void Job::add_rout(Operation *m)
{
    int t = m->time();
    if(t == 0)return;
    rout.append(m);
    grafZadanie* g = new grafZadanie(j, t, *col);
    grafiki.append(g);
    qDebug() << "dodalem punkt marszruty do zadania " << j;
}

QString Job::print() const
{
    QString s;
    Operation* m;
    bool f = false;
    foreach(m, this->rout)
    {
        if(m->time() > 0)
        {
            if(f)
                s += " - ";

            s += m->print();

            if(!f)
                f = true;
        }
    }
    return s;
}

int Job::time()
{
   return rout[cur]->time();
}

void Job::update()
{
    if(t < rj || blocked) return;
    if(cur >= rout.size())
    {
        blocked = true;

        Result* x = new Result(j, t, dj, rj);

        emit finished(x);
        return;
    }
    emit next(rout[cur]->machine(), this);
    blocked = true;
}

void Job::done()
{
    blocked = false;
    cur++;
}

QGraphicsItem* Job::gItem()
{
    return grafiki[cur];
}
