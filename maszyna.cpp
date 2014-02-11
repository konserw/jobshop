#include "maszyna.h"
#include "Job.h"
#include <QtDebug>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "common.h"

maszyna::maszyna(const QString &id, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_id(id),
    m_font(QFont("Arial", 10, QFont::Normal, false))
{
    setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

/*
    y = (id - 1) * (2 * grafZadanie::dy);
    x = 0;

    QGraphicsTextItem* text = scene->addText(s, *font);
    text->setX(x);
    text->setY(y);

    x += X0;
    scene->addLine(x, y, x, y+2*grafZadanie::dy, *pen);
    y += grafZadanie::dy;
*/
    QGraphicsTextItem* text = new QGraphicsTextItem(m_id, this);

    qDebug() << "utworzono maszyne" << m_id;
}

maszyna::~maszyna()
{
}

/*
void maszyna::start(Job* z)
{
    cur = z;
    stop = t + cur->time();

    QGraphicsItem* it = cur->gItem();
    it->setX(x);
    it->setY(y-cur->gItem()->boundingRect().height());
    scene->addItem(it);

    x += cur->gItem()->boundingRect().width();
}
*/

QString maszyna::id() const
{
    return m_id;
}

void maszyna::setId(const QString &id)
{
    m_id = id;
}

QRectF maszyna::boundingRect() const
{
    return QRectF();
}
Chromosome maszyna::chromosome() const
{
    return m_chromosome;
}

void maszyna::setChromosome(const Chromosome &chromosome)
{
    m_chromosome = chromosome;
}
QPen maszyna::pen() const
{
    return m_pen;
}

void maszyna::setPen(const QPen &pen)
{
    m_pen = pen;
}

void maszyna::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
/*
void maszyna::up2()
{
    if(cur)return;              //not null -> still procesing
    if(kolejka.isEmpty())       //nothing to do -> leave space
    {
        scene->addLine(x, y, x+grafZadanie::dx, y, *pen);
        x += grafZadanie::dx;
        return;
    }

    int size = kolejka.size();
    if(size > 1)        //konflikt -> krecha i numery konfliktowych zadan
    {
        scene->addLine(x, y-1.5*grafZadanie::dy, x, y+0.5*grafZadanie::dy, *penKonflikt);
        QString s("(");
        for(int i=0; i<size-1; ++i)
            s += QString::number(kolejka[i]->number()) + ", ";
        s += QString::number(kolejka[size-1]->number()) + ")";

        QGraphicsTextItem* text = scene->addText(s, *font);
        text->setDefaultTextColor(QColor(255, 0, 0));
        text->setX(x + 2);
        text->setY(y);
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
*/
