#include "EvolutionWindow.h"
#include "qcustomplot/qcustomplot.h"

#include <QtWidgets>

EvolutionWindow::EvolutionWindow(QWidget *parent) :
    QDialog(parent),
    m_iteration(0)
{
    setObjectName(QStringLiteral("EvolutionWindow"));
//    setWindowModality(Qt::ApplicationModal);
    resize(500, 500);

    m_layout = new QVBoxLayout(this);

    m_plot = new QCustomPlot(this);

    /*include this section to fully disable antialiasing for higher performance:
    m_plot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    m_plot->xAxis->setTickLabelFont(font);
    m_plot->yAxis->setTickLabelFont(font);
    m_plot->legend->setFont(font);
    */

    m_plot->addGraph(); // red line
    m_plot->graph(0)->setName(tr("worst chromosome"));
    m_plot->graph(0)->setPen(QPen(Qt::red));
    m_plot->graph(0)->setBrush(QBrush(Qt::gray));
    m_plot->graph(0)->setAntialiasedFill(false);
    m_plot->addGraph(); // green line
    m_plot->graph(1)->setName(tr("best chromosome"));
    m_plot->graph(1)->setPen(QPen(Qt::green));
    m_plot->graph(0)->setChannelFillGraph(m_plot->graph(1));
/*
    m_plot->addGraph(); // blue dot
    m_plot->graph(2)->setPen(QPen(Qt::red));
    m_plot->graph(2)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->addGraph(); // red dot
    m_plot->graph(3)->setPen(QPen(Qt::green));
    m_plot->graph(3)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);
*/

    m_plot->xAxis->setTickLabelType(QCPAxis::ltNumber);
    m_plot->xAxis->setAutoTickStep(false);
    m_plot->xAxis->setTickStep(5);
    m_plot->axisRect()->setupFullAxesBox();

    m_plot->xAxis->setLabel(tr("Iteration"));
    m_plot->yAxis->setLabel("Fitness value");
    m_plot->legend->setVisible(true);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(m_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_plot->yAxis2, SLOT(setRange(QCPRange)));

    m_layout->addWidget(m_plot);
}

EvolutionWindow::~EvolutionWindow()
{
    //    delete m_plot;
}

void EvolutionWindow::plot(double low, double hi)
{
    // add data to lines:
    m_plot->graph(0)->addData(m_iteration, low);
    m_plot->graph(1)->addData(m_iteration, hi);
    // set data of dots:
    /*
    m_plot->graph(2)->clearData();
    m_plot->graph(2)->addData(m_iteration, low);
    m_plot->graph(3)->clearData();
    m_plot->graph(3)->addData(m_iteration, hi);
    */
    // remove data of lines that's outside visible range:
//    m_plot->graph(0)->removeDataBefore(key-8);
//    m_plot->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    m_plot->graph(0)->rescaleValueAxis();
    m_plot->graph(1)->rescaleValueAxis(true);


  // make key axis range scroll with the data (at a constant range size of 8):
    m_plot->xAxis->setRange(m_iteration, m_iteration, Qt::AlignRight);
    m_plot->replot();

    m_iteration++;
}
