#include "grafZadanie.h"
#include <QPainter>
#include <QtGui>
//#include "czas.h"
#include "common.h"

grafZadanie::grafZadanie(int id, int time, QColor& color)
{
    w = time*dx;
    h = dy;
    j = QString::number(id);
    col = color;
}

grafZadanie::~grafZadanie()
{

}

QRectF grafZadanie::boundingRect() const
{
    return QRectF(0, 0, w, h);
}

void grafZadanie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QFont font("Helvetica", 10, QFont::Bold, false);
    QPen pen;
    pen.setWidth(0);

    QRectF rect(this->boundingRect());

    painter->setPen(pen);
    painter->setBrush(col);
    painter->drawRect(rect);

    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter, j);
}
