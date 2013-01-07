#include "maszyna.h"
#include "zadanie.h"
#include <qdebug.h>
#include "common.h"

int maszyna::method = 0;

maszyna::maszyna(int id, QGraphicsScene *sc)
{
    _id = id;
    cur = NULL;

    QString s = tr("Maszyna ");
    s += QString::number(id);

    scene = sc;
    y = (id-1)*40;
    x = 0;
    font = new QFont("Arial", 10, QFont::Normal, false);
    pen = new QPen();
    penKonflikt = new QPen(QColor(255, 0, 0));
    penKonflikt->setWidth(5);
    pen->setWidth(1);

    QGraphicsTextItem* text = scene->addText(s, *font);
    text->setX(x);
    text->setY(y);

    x += 80;
    scene->addLine(x, y, x, y+20, *pen);
    y += 20;

    DEBUG << "utworzono maszyne nr " << id;
}

maszyna::~maszyna()
{
    delete penKonflikt;
    delete pen;
    delete font;
}

void maszyna::add(zadanie *z)
{
    kolejka.append(z);
}

void maszyna::start(zadanie* z)
{
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

    int size = kolejka.size();
    if(size > 1)        //konflikt -> krecha i numery konfliktowych zadan
    {
        scene->addLine(x, y-1.5*dy, x, y+0.5*dy, *penKonflikt);
        QString s("(");
        for(int i=0; i<size-1; ++i)
            s += QString::number(kolejka[i]->number()) + ", ";
        s += QString::number(kolejka[size-1]->number()) + ")";

        QGraphicsTextItem* text = scene->addText(s, *font);
        text->setDefaultTextColor(QColor(255, 0, 0));
        text->setX(x + 2);
        text->setY(y);// + (0.5*dy));// - text->boundingRect().height());
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
