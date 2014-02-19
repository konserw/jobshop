#ifndef GRAFZADANIE_H
#define GRAFZADANIE_H

#include <QGraphicsItem>
#include <QString>

class GanttOperation : public QGraphicsItem
{
public:
    GanttOperation(const QString& id, int time, const QColor& color);
    ~GanttOperation();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    static const int m_widthUnit = 9;
    static const int m_height = 20;

protected:
    QString m_id;
    qreal m_width;
    const QColor& m_color;
};

#endif // GRAFZADANIE_H
