#ifndef GRAFZADANIE_H
#define GRAFZADANIE_H

#include <QGraphicsItem>

class grafZadanie : public QGraphicsItem
{
public:
    grafZadanie(int id, int time, QColor& color);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    ~grafZadanie();
protected:
    QString j;
    qreal w, h;
    QColor col;
};

#endif // GRAFZADANIE_H
