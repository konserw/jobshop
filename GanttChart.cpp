#include "GanttChart.h"
#include "Jobshop.h"
#include <algorithm>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsLineItem>
#include <QFont>
#include <QPen>

GanttChart::GanttChart(int cMax) :
    QGraphicsItem(nullptr),
    m_cMax(cMax)
{
    QGraphicsLineItem* line;
    QGraphicsSimpleTextItem* text;
    QFont font("Arial", 12);
    double x;
    double ym = GanttChart::machineHeight * Jobshop::instance()->machinesCount()  + operationHeight;
//siatka
    for(int i=0; i<cMax; i+=5)
    {
        x = machineHorizontalOffset + widthUnit*i;
        line = new QGraphicsLineItem(x, operationHeight, x, ym, this);
        text = new QGraphicsSimpleTextItem(QString::number(i), this);
        text->setFont(font);
        text->setX(x+3);
        text->setY(ym-15);
    }
//linia z Cmax
    x = machineHorizontalOffset + m_cMax * widthUnit;
    line = new QGraphicsLineItem(x, operationHeight, x, ym, this);
    line->setPen(QPen(Qt::red));
    text = new QGraphicsSimpleTextItem(QString("Cmax = %1").arg(cMax), this);
    text->setFont(font);
    text->setX(x+3);
    text->setY(ym-15);
}

QRectF GanttChart::boundingRect() const
{
    double width = machineHorizontalOffset + (m_cMax + 4) * widthUnit;
    double height = GanttChart::machineHeight * (Jobshop::instance()->machinesCount() + 1);
    return QRectF(0, 0, width, height);
}

void GanttChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
}
