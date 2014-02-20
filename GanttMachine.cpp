#include "GanttChart.h"
#include "GanttMachine.h"

#include <QtDebug>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QFont>

GanttMachine::GanttMachine(const QString &id, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_id(id),
    m_cMax(0)
{
    m_pen = QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QGraphicsTextItem* text = new QGraphicsTextItem(m_id, this);
    text->setPos(0, GanttChart::machineHeight/2);
    text->setFont(QFont("Arial", 12, QFont::Normal, false));

    qDebug() << "utworzono maszyne" << m_id;
}

GanttMachine::~GanttMachine()
{
}

QRectF GanttMachine::boundingRect() const
{
    return QRectF(0, 0, GanttChart::machineHorizontalOffset + (m_cMax + 5) * GanttChart::widthUnit, GanttChart::machineHeight);
}

void GanttMachine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(m_pen);

}

void GanttMachine::setCMax(int cMax)
{
    m_cMax = cMax;
}
