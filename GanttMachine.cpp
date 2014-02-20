#include "Arrow.h"
#include "GanttChart.h"
#include "GanttMachine.h"

#include <QPen>
#include <QtDebug>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QFont>

GanttMachine::GanttMachine(const QString &id, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_id(id),
    m_cMax(0)
{   
    QGraphicsTextItem* text = new QGraphicsTextItem(m_id, this);
    text->setPos(0, GanttChart::machineHeight/2);
    text->setFont(QFont("Arial", 12, QFont::Normal, false));


    QGraphicsLineItem* line = new QGraphicsLineItem(GanttChart::machineHorizontalOffset, 0, GanttChart::machineHorizontalOffset, GanttChart::machineHeight, this);
    QPen pen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    line->setPen(pen);

    m_arrow = new Arrow(this);
    m_arrow->setPen(pen);
}

GanttMachine::~GanttMachine()
{
}

QRectF GanttMachine::boundingRect() const
{
    const QPointF& p = m_arrow->boundingRect().bottomRight();
    return QRectF(0, 0, p.x(), p.y());
}

void GanttMachine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
}

void GanttMachine::setCMax(int cMax)
{
    m_cMax = cMax;

    QPointF p(0, GanttChart::machineHeight);
    m_arrow->setStartPoint(p);
    p.rx() += GanttChart::machineHorizontalOffset + (m_cMax + 4) * GanttChart::widthUnit;
    m_arrow->setEndPoint(p);
}
