#ifndef EVOLUTIONWINDOW_H
#define EVOLUTIONWINDOW_H

#include <QDialog>
#include <QTimer>
#include "Chromosome.h"

QT_BEGIN_NAMESPACE
class QCustomPlot;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QSlider;
//class QLabel;
QT_END_NAMESPACE

/*!
 * \brief The EvolutionWindow class - dialog window showing evolution progress
 *
 * uses QCustomPlot from http://www.qcustomplot.com/
 */
class EvolutionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EvolutionWindow(QWidget *parent = 0);
    ~EvolutionWindow();

    void rescalePlot();

public slots:
    void plot(double low, double hi);
    void toggleRun();
    void refRange(int range);
    void refInterval(int inter);
    void showResult();

protected:
    QCustomPlot* m_plot;
    QVBoxLayout* m_layout;
    QHBoxLayout* m_h1;
    QHBoxLayout* m_h2;
    QHBoxLayout* m_h3;
    /*
    QLabel* m_rangeLabel;
    QLabel* m_intervalLabel;
    */
    QPushButton* m_stopButton;
    QPushButton* m_pauseButton;
    QSlider* m_range;
    QSlider* m_interval;

    int m_iteration;
    QTimer m_timer;
    bool m_isRunning;

    static const int m_maxRange = 1000;
    int m_plotRange;

    double m_fifoValue;
    double m_lifoValue;
};

#endif // EVOLUTIONWINDOW_H
