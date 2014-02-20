#ifndef GANTTCHART_H
#define GANTTCHART_H

#include <QGraphicsItem>

class GanttChart : public QGraphicsItem
{
    Q_INTERFACES(QGraphicsItem)

public:
    GanttChart(int cMax);

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

protected:
    ///Metoda rysująca graficzą reprezentację obiektu.
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    int m_cMax;
};

#endif // GANTTCHART_H
