#ifndef WYKRES_H
#define WYKRES_H

#include "Chromosome.h"
#include "GanttChart.h"
#include <QDialog>

class Result;
class QGraphicsScene;
class QDir;
class Job;

namespace Ui {
    class ResultWindow;
}

class ResultWindow : public QDialog {
    Q_OBJECT

public:
    ResultWindow(const Chromosome& chromosome, QWidget *parent);
    ~ResultWindow();

public slots:
//    void pdf();
//    void pdf(const QString&fileName);
    void latex();
    void latex2(const QString&);
    void saveChart();
    void save2(const QString& filename);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ResultWindow *ui;

    Chromosome m_chromosome;

    GanttChart* m_chart;
    QGraphicsScene* m_scene;

};

#endif // WYKRES_H
