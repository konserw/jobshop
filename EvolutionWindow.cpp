#include "EvolutionWindow.h"
#include "qcustomplot/qcustomplot.h"

#include <QtWidgets>
#include "Jobshop.h"
#include "ResultWindow.h"

EvolutionWindow::EvolutionWindow(QWidget *parent) :
    QDialog(parent),
    m_iteration(0),
    m_isRunning(false),
    m_plotRange(25)
{
    Jobshop::instance()->generateInitialPopulation();

    m_fifoValue = Jobshop::instance()->fifoValue();
    m_lifoValue = Jobshop::instance()->lifoValue();

    setWindowTitle(tr("Evolution process"));
    setWindowIcon(QIcon(":/logo"));
    setObjectName(QStringLiteral("EvolutionWindow"));
    setWindowModality(Qt::ApplicationModal);
    resize(500, 500);

    m_layout = new QVBoxLayout(this);

    m_h1 = new QHBoxLayout();
    m_pauseButton = new QPushButton(tr("Pause/Start"), this);
    m_h1->addWidget(m_pauseButton);
    m_resultCombo = new QComboBox(this);
    m_resultCombo->addItem(tr("Best chromosome"));
    m_resultCombo->addItem(tr("Worst chromosome"));
    m_resultCombo->addItem(tr("FIFO cheuristic"));
    m_resultCombo->addItem(tr("LIFO cheuristic"));
    m_h1->addWidget(m_resultCombo);
    m_stopButton = new QPushButton(tr("Show result"), this);
    m_h1->addWidget(m_stopButton);
    m_h1->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding));

    m_layout->addLayout(m_h1);

    m_h2 = new QHBoxLayout();
    m_h2->addWidget(new QLabel(tr("Plot range:"), this));
    m_range = new QSlider(Qt::Horizontal, this);
    m_range->setMinimum(5);
    m_range->setMaximum(m_maxRange);
    m_range->setSingleStep(5);
    m_range->setValue(m_plotRange);
    m_h2->addWidget(m_range);

    m_layout->addLayout(m_h2);

    m_h3 = new QHBoxLayout();
    m_h3->addWidget(new QLabel(tr("Reproduction interval"), this));
    m_interval = new QSlider(Qt::Horizontal, this);
    m_interval->setMinimum(0);
    m_interval->setMaximum(1000);
    m_interval->setSingleStep(5);
    m_interval->setValue(100);
    m_h3->addWidget(m_interval);

    m_layout->addLayout(m_h3);

    m_plot = new QCustomPlot(this);

    m_plot->addGraph(); // red line
    m_plot->graph(0)->setName(tr("worst chromosome"));
    m_plot->graph(0)->setPen(QPen(Qt::red));
    m_plot->graph(0)->setBrush(QBrush(Qt::gray));
    m_plot->graph(0)->setAntialiasedFill(false);
    m_plot->addGraph(); // red dot
    m_plot->graph(1)->setName(tr("worst chromosome value"));
    m_plot->graph(1)->setPen(QPen(Qt::red));
    m_plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);

    m_plot->addGraph(); // green line
    m_plot->graph(2)->setName(tr("best chromosome"));
    m_plot->graph(2)->setPen(QPen(Qt::green));
    m_plot->graph(0)->setChannelFillGraph(m_plot->graph(2));
    m_plot->addGraph(); // green dot
    m_plot->graph(3)->setName(tr("best chromosome value"));
    m_plot->graph(3)->setPen(QPen(Qt::green));
    m_plot->graph(3)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    m_plot->addGraph(); // blue dot - fifo
    m_plot->graph(4)->setName(tr("FIFO value = %1").arg(m_fifoValue));
    m_plot->graph(4)->setPen(QPen(Qt::blue));
    m_plot->graph(4)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(4)->setScatterStyle(QCPScatterStyle::ssDisc);

    m_plot->addGraph(); // black dot - lifo
    m_plot->graph(5)->setName(tr("LIFO value = %1").arg(m_lifoValue));
    m_plot->graph(5)->setPen(QPen(Qt::black));
    m_plot->graph(5)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(5)->setScatterStyle(QCPScatterStyle::ssDisc);

    m_plot->xAxis->setTickLabelType(QCPAxis::ltNumber);
    m_plot->xAxis->setAutoTickStep(false);
    m_plot->xAxis->setTickStep(5);
    m_plot->axisRect()->setupFullAxesBox();

    m_plot->xAxis->setLabel(tr("Iteration"));
    m_plot->yAxis->setLabel("Fitness value");
    m_plot->legend->setVisible(true);

    m_layout->addWidget(m_plot);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(m_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_plot->yAxis2, SLOT(setRange(QCPRange)));

    connect(m_pauseButton, &QPushButton::clicked, this, &EvolutionWindow::toggleRun);
    connect(Jobshop::instance(), &Jobshop::iterationResult, this, &EvolutionWindow::plot);
    connect(&m_timer, &QTimer::timeout, Jobshop::instance(), &Jobshop::iteration);
    connect(m_range, &QSlider::valueChanged, this, &EvolutionWindow::refRange);
    connect(m_interval, &QSlider::valueChanged, this, &EvolutionWindow::refInterval);
    connect(m_stopButton, &QPushButton::clicked, this, &EvolutionWindow::showResult);
}

EvolutionWindow::~EvolutionWindow()
{
}

void EvolutionWindow::toggleRun()
{
    if(m_isRunning) //stop
    {
        m_timer.stop();
        m_isRunning = false;
    }
    else //start
    {
        m_timer.setInterval(m_interval->value());
        m_timer.start();
        m_isRunning = true;
    }
}

void EvolutionWindow::refInterval(int inter)
{
    m_timer.setInterval(inter);
}

void EvolutionWindow::showResult()
{
    if(m_isRunning)
        toggleRun();

    ResultWindow* rw;

    switch(m_resultCombo->currentIndex())
    {
    case 0:
        rw = new ResultWindow(Jobshop::instance()->winnerChromosome(), this);
        break;
    case 1:
        rw = new ResultWindow(Jobshop::instance()->looserChromosome(), this);
        break;
    case 2:
        rw = new ResultWindow(Jobshop::instance()->fifoChromosome(), this);
        break;
    case 3:
        rw = new ResultWindow(Jobshop::instance()->lifoChromosome(), this);
        break;
    }

    rw->showMaximized();
    rw->exec();
}

void EvolutionWindow::rescalePlot()
{
    int first = std::max(0, m_iteration-m_plotRange);
    // rescale value (vertical) axis to fit the current data:
    m_plot->yAxis->setRange(m_plot->graph(2)->data()->value(m_iteration-1).value *0.99, m_plot->graph(0)->data()->value(first).value * 1.01);
    // make key axis range scroll with the data
    m_plot->xAxis->setRange(m_iteration+1, m_plotRange, Qt::AlignRight);
    m_plot->replot();
}

void EvolutionWindow::refRange(int range)
{
    m_plotRange = range;
    rescalePlot();
}

void EvolutionWindow::plot(double low, double hi)
{      
    m_plot->graph(1)->setName(tr("value = %1").arg(low));
    m_plot->graph(3)->setName(tr("value = %1").arg(hi));
    // add data to lines:
    m_plot->graph(0)->addData(m_iteration, low);
    m_plot->graph(2)->addData(m_iteration, hi);
    // set data of dots:
    m_plot->graph(1)->clearData();
    m_plot->graph(1)->addData(m_iteration, low);
    m_plot->graph(3)->clearData();
    m_plot->graph(3)->addData(m_iteration, hi);
    m_plot->graph(4)->clearData();
    m_plot->graph(4)->addData(m_iteration, m_fifoValue);
    m_plot->graph(5)->clearData();
    m_plot->graph(5)->addData(m_iteration, m_lifoValue);
    // remove data of lines that's outside maximum range:
    m_plot->graph(0)->removeDataBefore(m_iteration-m_maxRange);
    m_plot->graph(2)->removeDataBefore(m_iteration-m_maxRange);

    rescalePlot();
    m_iteration++;
}
