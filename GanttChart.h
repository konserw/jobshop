#ifndef GANTTCHART_H
#define GANTTCHART_H

#include <QGraphicsItemGroup>

class GanttChart : public QGraphicsItemGroup
{
    Q_INTERFACES(QGraphicsItem)

public:
    GanttChart();

    static const int widthUnit = 20;
    static const int operationHeight = 20;

    static QPointF operationPosition(int time)
    { return QPointF(time * widthUnit, 0); }

    static const int machineHeight = operationHeight * 3;
    static const int machineHorizontalOffset = 35;

    static QPointF machineOffset()
    { return QPointF(machineHorizontalOffset, machineHeight - operationHeight - 1); }

    ///Zwraca prostokąt wewnątrz którego odbywa się rysowanie.
    virtual QRectF boundingRect() const;

    QPointF corner() const;
    void setCorner(const QPointF &corner);

protected:
    QPointF m_corner;

};

#endif // GANTTCHART_H
