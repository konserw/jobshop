#include "GanttChart.h"
#include <algorithm>

GanttChart::GanttChart() :
    QGraphicsItemGroup(nullptr)
{
}

QRectF GanttChart::boundingRect() const
{
/*
    auto children = this->childItems();
    auto cornerItemIterator = std::max_element(
                children.begin(),
                children.end(),
                [] (QGraphicsItem* a, QGraphicsItem* b) -> bool
    {
            double av = a->mapToParent(a->boundingRect().bottomLeft()).y();
            double bv = b->mapToParent(b->boundingRect().bottomLeft()).y();
            return (av < bv);
    }
                );
    QPointF corner = this->mapFromItem(*cornerItemIterator, (*cornerItemIterator)->boundingRect().bottomLeft());
    return QRectF(QPointF(0, 0), corner);
    */
    return QRectF(QPointF(0, 0), m_corner);
}
QPointF GanttChart::corner() const
{
    return m_corner;
}

void GanttChart::setCorner(const QPointF &corner)
{
    m_corner = corner;
}



