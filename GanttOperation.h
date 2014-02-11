#ifndef GRAFZADANIE_H
#define GRAFZADANIE_H

#include <QGraphicsItem>

class GanttOperation : public QGraphicsItem
{
public:
    GanttOperation(int id, int time, QColor& color);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    ~GanttOperation();

    static const int dx = 9;
    static const int dy = 20;

protected:
    QString j;
    qreal w, h;
    QColor col;
};

#endif // GRAFZADANIE_H
