#include "maszyna.h"
#include "zadanie.h"
#include <qdebug.h>
#include "common.h"

int maszyna::method = 0;

maszyna::maszyna(int id, QGraphicsScene *sc)
{
    _id = id;
    cur = NULL;

    QString s = "maszyna";
    s += QString::number(id);
    f = new QFile(s);
    f->open(QIODevice::WriteOnly | QIODevice::Text);
    ts = new QTextStream(f);

    scene = sc;
    y = (id-1)*40;
    x = 0;
    font = new QFont("Helvetica", 12, QFont::Normal, false);
    pen = new QPen();
    pen->setWidth(1);

    QGraphicsTextItem* text = scene->addText(s, *font);
    text->setX(x);
    text->setY(y);

    x += 80;
    scene->addLine(x, y, x, y+20, *pen);
    y += 20;

    line = scene->addLine(x, y, x+200, y, *pen);

    *ts << "czas|zadanie|czynnosc\n";
    DEBUG << "utworzono maszyne nr " << id;
}

maszyna::~maszyna()
{
    delete f;
    delete ts;

    delete pen;
    delete font;
}

void maszyna::add(zadanie *z)
{
    *ts << t << "\t| " << z->number() << "\t| " << "otrzymano zlecenie\n";

    kolejka.append(z);
}

void maszyna::start(zadanie* z)
{
    *ts << t << "\t| " << z->number() << "\t| " << "poczatek zadania\n";
    cur = z;
    stop = t + cur->time();

    QGraphicsItem* it = cur->gItem();
    it->setX(x);
    it->setY(y-cur->gItem()->boundingRect().height());
    scene->addItem(it);

    x += cur->gItem()->boundingRect().width();
}

void maszyna::update()
{
    if(t >= stop && cur != NULL)
    {
        *ts << t << "\t| " << cur->number() << "\t| " << "zadanie zakonczone\n";

        cur->done();
        cur = NULL;
    }
}
void maszyna::up2()
{
    if(cur)return;              //not null -> still procesing
    if(kolejka.isEmpty())       //nothing to do -> leave space
    {
        scene->addLine(x, y, x+dx, y, *pen);
        x += dx;
        return;
    }

    switch(method)
    {
    case 0://fifo
        start(kolejka.first());
        kolejka.removeFirst();
        break;
    case 1://lifo
        start(kolejka.last());
        kolejka.removeLast();
        break;
    }
}
