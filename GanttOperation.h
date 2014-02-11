#ifndef GRAFZADANIE_H
#define GRAFZADANIE_H

#include <QGraphicsItem>
#include <QString>

class GanttOperation : public QGraphicsItem
{
public:
    GanttOperation(const QString& id, int time, QColor& color);
    ~GanttOperation();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    static const int dx = 9;
    static const int dy = 20;

protected:
    QString m_id;
    qreal w, h;
    QColor col;
};

#endif // GRAFZADANIE_H
