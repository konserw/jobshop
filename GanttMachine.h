#ifndef MASZYNA_H
#define MASZYNA_H

#include <QGraphicsItem>

class Arrow;

class GanttMachine : public QGraphicsItem
{
    Q_INTERFACES(QGraphicsItem)

public:
    GanttMachine(const QString& id, QGraphicsItem *parent = 0);
    ~GanttMachine();

    ///Zwraca prostokąt wewnątrz którego odbywa się rysowanie.
    virtual QRectF boundingRect() const;

    void setCMax(int cMax);

protected:
    ///Metoda rysująca graficzą reprezentację obiektu.
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    int m_cMax;
    QString m_id;
    Arrow* m_arrow;
};

#endif // MASZYNA_H
