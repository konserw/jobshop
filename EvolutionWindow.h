#ifndef EVOLUTIONWINDOW_H
#define EVOLUTIONWINDOW_H

#include <QDialog>

class QCustomPlot;
class QVBoxLayout;

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

public slots:
    void plot(double low, double hi);

protected:
    QCustomPlot* m_plot;
    QVBoxLayout* m_layout;

    int m_iteration;
};

#endif // EVOLUTIONWINDOW_H
