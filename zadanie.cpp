#include "zadanie.h"
#include "marszruta.h"
#include <qdebug.h>
#include "common.h"


zadanie::zadanie(int number, int start_time, int due_date)
{
    j = number;
    rj = start_time;
    dj = due_date;

    cur=0;
    blocked = false;

    col =  new QColor(qrand() % 256, qrand() % 256, qrand() % 256);

    DEBUG << "utworzono zadanie nr " << j << " rj: " << rj << " dj: " << dj;
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
    DEBUG << "dodalem punkt marszruty do zadania " << j;
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

        stat* x = new stat(j, t, dj, rj);

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
