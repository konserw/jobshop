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

    static const int dx = 9;
    static const int dy = 20;

protected:
    QString j;
    qreal w, h;
    QColor col;
};

#endif // GRAFZADANIE_H
