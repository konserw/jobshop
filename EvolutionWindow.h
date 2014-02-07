#ifndef EVOLUTIONWINDOW_H
#define EVOLUTIONWINDOW_H

#include <QDialog>

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

signals:

public slots:

};

#endif // EVOLUTIONWINDOW_H
