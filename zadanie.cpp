#include "zadanie.h"
#include "marszruta.h"
#include "common.h"
#include "result.h"
#include <QtDebug>

zadanie::zadanie(int number, int start_time, int due_date)
{
    j = number;
    rj = start_time;
    dj = due_date;

    cur=0;
    blocked = false;

    col =  new QColor(qrand() % 256, qrand() % 256, qrand() % 256);

    qDebug() << "utworzono zadanie nr " << j << " rj: " << rj << " dj: " << dj;
}

zadanie::~zadanie()
{
    delete col;
}

void zadanie::add_rout(marszruta *m)
{
    int t = m->time();
    if(t == 0)return;
    rout.append(m);
    grafZadanie* g = new grafZadanie(j, t, *col);
    grafiki.append(g);
    qDebug() << "dodalem punkt marszruty do zadania " << j;
}

QString zadanie::print() const
{
    QString s;
    marszruta* m;
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

int zadanie::time()
{
   return rout[cur]->time();
}

void zadanie::update()
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

void zadanie::done()
{
    blocked = false;
    cur++;
}

QGraphicsItem* zadanie::gItem()
{
    return grafiki[cur];
}
