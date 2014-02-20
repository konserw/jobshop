#ifndef GRAFZADANIE_H
#define GRAFZADANIE_H

#include <QGraphicsRectItem>
#include <QString>

class GanttOperation : public QGraphicsRectItem
{
    Q_INTERFACES(QGraphicsItem)

public:
    GanttOperation(const QString& id, int time, const QColor& color);
    ~GanttOperation();

    QPointF position(int time);

    static const int m_widthUnit = 20;
    static const int m_height = 20;

protected:    
    ///Metoda rysująca graficzą reprezentację obiektu.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString m_id;
    qreal m_width;
    const QColor& m_color;
};

#endif // GRAFZADANIE_H
