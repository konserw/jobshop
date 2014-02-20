#include "GanttMachine.h"
#include "Job.h"
#include <QtDebug>
#include <QGraphicsTextItem>
#include <QPainter>

GanttMachine::GanttMachine(const QString &id, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_id(id),
    m_cMax(0)
{
    m_pen = QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

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
    text->setPos(0, m_height/2);
    text->setFont(QFont("Arial", 12, QFont::Normal, false));

    qDebug() << "utworzono maszyne" << m_id;
}

GanttMachine::~GanttMachine()
{
}

QString GanttMachine::id() const
{
    return m_id;
}

void GanttMachine::setId(const QString &id)
{
    m_id = id;
}

QRectF GanttMachine::boundingRect() const
{
    return QRectF(0, 0, m_xOffset + (m_cMax + 5) * GanttOperation::m_widthUnit, m_height);
}

void GanttMachine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
/*
    qDebug() << boundingRect();
    painter->setPen(m_pen);
    painter->drawRect(boundingRect());
*/
}

void GanttMachine::setCMax(int cMax)
{
    m_cMax = cMax;
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
