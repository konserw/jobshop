#include "GanttOperation.h"
#include <QPainter>

GanttOperation::GanttOperation(const QString& id, int time, const QColor &color) :
    QGraphicsRectItem(nullptr),
    m_color(color)
{
    m_id = id;
    m_width = time*m_widthUnit;
    this->setRect(0, 0, m_width, m_height);
}

GanttOperation::~GanttOperation()
{
}
/*
QRectF GanttOperation::boundingRect() const
{
    return QRectF();
}
*/
void GanttOperation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QFont font("Helvetica", 10, QFont::Bold, false);
    QPen pen;
    pen.setWidth(0);

    const QRectF& rect = this->rect();

    painter->setPen(pen);
    painter->setBrush(m_color);
    painter->drawRect(rect);

    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter, m_id);
}
