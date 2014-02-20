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

    void setTime(int time);

protected:    
    ///Metoda rysująca graficzą reprezentację obiektu.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString m_id;
    const QColor& m_color;
};

#endif // GRAFZADANIE_H
