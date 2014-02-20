#ifndef GANTTCHART_H
#define GANTTCHART_H

#include <QGraphicsItemGroup>

class GanttChart : public QGraphicsItemGroup
{
    Q_INTERFACES(QGraphicsItem)

public:
    GanttChart();
};

#endif // GANTTCHART_H
