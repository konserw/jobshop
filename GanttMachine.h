#ifndef MASZYNA_H
#define MASZYNA_H

#include <QGraphicsItem>
#include <QFont>
#include <QPen>
#include <QList>

#include "Chromosome.h"
#include "GanttOperation.h"

class GanttMachine : public QGraphicsItem
{
    Q_INTERFACES(QGraphicsItem)

public:
    GanttMachine(const QString& id, QGraphicsItem *parent = 0);
    ~GanttMachine();

    QString id() const;
    void setId(const QString &id);

    ///Zwraca prostokąt wewnątrz którego odbywa się rysowanie.
    virtual QRectF boundingRect() const;

    Chromosome chromosome() const;
    void setChromosome(const Chromosome &chromosome);

    QPen pen() const;
    void setPen(const QPen &pen);

protected:
    ///Metoda rysująca graficzą reprezentację obiektu.
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);


private:
    int stop;
    QString m_id;

    QPen m_pen;
    QFont m_font;
    QList<GanttOperation> m_opertionGraphics;

    static const int X0 = 35;
};

#endif // MASZYNA_H
