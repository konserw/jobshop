#include "GanttChart.h"
#include "Jobshop.h"
#include <algorithm>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsLineItem>
#include <QFont>
#include <QPen>
#include <QtSvg/QSvgGenerator>
#include <QPainter>
#include <QtDebug>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>

GanttChart::GanttChart(int cMax) :
    QGraphicsItem(nullptr),
    m_cMax(cMax)
{
    QGraphicsLineItem* line;
    QGraphicsSimpleTextItem* text;
    QFont font("Arial", 12);
    double x;
    double ym = GanttChart::machineHeight * Jobshop::instance()->machinesCount()  + operationHeight;
//siatka
    for(int i=0; i<cMax; i+=5)
    {
        x = machineHorizontalOffset + widthUnit*i;
        line = new QGraphicsLineItem(x, operationHeight, x, ym, this);
        text = new QGraphicsSimpleTextItem(QString::number(i), this);
        text->setFont(font);
        text->setX(x+3);
        text->setY(ym-15);
    }
//linia z Cmax
    x = machineHorizontalOffset + m_cMax * widthUnit;
    line = new QGraphicsLineItem(x, operationHeight, x, ym, this);
    line->setPen(QPen(Qt::red));
    text = new QGraphicsSimpleTextItem(QString("Cmax = %1").arg(cMax), this);
    text->setFont(font);
    text->setX(x+3);
    text->setY(ym-15);
}

QRectF GanttChart::boundingRect() const
{
    return this->childrenBoundingRect();
}
/*
void GanttChart::save(const QString &filename)
{
    QSvgGenerator svgGen;
    svgGen.setFileName(filename);
    QRectF r = boundingRect();
    QSize s = r.size().toSize();
    qDebug() << "image size:" << r << s;
    svgGen.setSize(s);
    svgGen.setViewBox(r);
    svgGen.setResolution(300);
    svgGen.setTitle(QObject::tr("Gantt chart"));
    svgGen.setDescription(QObject::tr("Gantt chart"));
    QImage im(s);
    im.fill(Qt::white);
    QPainter painter;
    painter.begin(&svgGen);
    im.
    painter.end();
}
*/
void GanttChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
