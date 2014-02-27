#include "Chromosome.h"
#include "Jobshop.h"
#include "Job.h"
#include "Operation.h"

#include "GanttMachine.h"
#include "GanttOperation.h"
#include "GanttChart.h"

#include <QVector>
#include <random>
#include <algorithm>
#include <QtDebug>
#include <QtWidgets>

Chromosome::Chromosome() :
    m_valueMean(-1),
    m_valueAlpha(-1),
    m_chart(nullptr),
    m_summary(nullptr)
{
}

Chromosome::~Chromosome()
{
    delete m_chart;
    delete m_summary;
}

int Chromosome::geneCount() const
{
    return m_genes.count();
}

bool Chromosome::hasGene(const QString &gene) const
{
    return m_genes.contains(gene);
}

double Chromosome::value() const
{
    if(Jobshop::instance()->fitnessFunction() == Jobshop::SquareMean)
        return m_valueMean;
    else
        return m_valueAlpha;
}

double Chromosome::valueMean() const
{
    return m_valueMean;
}

double Chromosome::valueAlpha() const
{
    return m_valueAlpha;
}

int Chromosome::completionTime() const
{
    return std::max_element(
                m_results.begin(),
                m_results.end(),
                [] (const Result& a, const Result& b) -> bool { return a.completionTime() < b.completionTime(); }
    )->completionTime();
}

double Chromosome::meanFlow() const
{
    return m_meanFlow;
}

int Chromosome::tardy() const
{
    return m_numberOfTardy;
}

int Chromosome::maxTardy() const
{
    return std::max_element(
                m_results.begin(),
                m_results.end(),
                [] (const Result& a, const Result& b) -> bool { return a.lateness() < b.lateness(); }
    )->lateness();
}

double Chromosome::meanTardy() const
{
    return m_meanTardy;
}

bool Chromosome::operator<(const Chromosome& other) const
{
    return value() < other.value();
}

bool Chromosome::operator>(const Chromosome& other) const
{
    return value() > other.value();
}

const QList<Result> &Chromosome::results() const
{
    return m_results;
}

int Chromosome::startTime(const QString &operation) const
{
    return m_operationsStartTime[operation];
}

GanttChart* Chromosome::ganttChart()
{
    if(m_chart == nullptr)
    {
        int cMax = completionTime();
        m_chart = new GanttChart(cMax);

        QList<GanttMachine*> machines;
        GanttMachine* m;
        int machinesCount = Jobshop::instance()->machinesCount();
        for(int i=0; i<machinesCount; ++i)
        {
            m = new GanttMachine(QString("m%1").arg(i+1), m_chart);
            machines.append(m);
            m->setPos(0, i * GanttChart::machineHeight);
            m->setCMax(cMax);
        }

        for(const QString& opId : m_genes)
        {
            const Operation& op = Jobshop::instance()->operation(opId);
            GanttOperation* gop = op.ganttGraphic();
            gop->setParentItem(machines[op.machine()]);
            QPointF pos = GanttChart::operationPosition(startTime(opId));
            gop->setPos(pos + GanttChart::machineOffset());
        }
    }

    return m_chart;
}

const QString& Chromosome::latexSummary()
{
    if(m_summary == nullptr)
    {
        QString s;
        s =
                "%Tabela wynikowa\n\n"
                "\\begin{table}[htb]\n"
                "\t\\centering\n"
                "\t\\caption{Parametry wykonanych zadań}\n"
                "\t\\begin{tabular}{ | r | c | c | c | c |}\n"
                "\t\t\\hline\n"
                "\t\tJob\t& \\(C_i\\)\t& \\(f_i\\)\t& \\(T_i\\)\t& \\(E_i\\)\t\\\\ \\hline\n";

            for(const Result& result : m_results)
            {
                s += QString("\t\t%1\t& %2\t& %3\t& %4\t& %5\t\\\\ \\hline\n")
                        .arg(result.jobID())
                        .arg(result.completionTime())
                        .arg(result.flow())
                        .arg(result.lateness())
                        .arg(result.earliness());
            }

            s +=    "\t\\end{tabular}\n"
                    "\\end{table}\n"
                    "\n"
                    "%Tabela wyznacznikow\n\n"
                    "\\begin{table}[htb]\n"
                    "\t\\centering\n"
                    "\t\\begin{tabular}{ l l l }\n";

            s +=    QString(
                        "\t\t\\(C_{max} = %1 \\)\t& \\( T_{max} = %3 \\)\t& \\( \\sqrt{\\sum E_i^2 + \\sum T_i^2} = %5 \\)\t\\\\\n"
                        "\t\t\\( \\bar{F} = %2 \\)\t& \\( \\bar{T} = %4 \\)\t& \\( \\sum \\left( \\alpha_i * E_i + \\beta_i * T_i \\right) = %6 \\)\t\\\\\n"
                        )
                    .arg(completionTime())
                    .arg(meanFlow())
                    .arg(maxTardy())
                    .arg(meanTardy())
                    .arg(valueMean())
                    .arg(valueAlpha());

            s +=    "\t\\end{tabular}\n"
                    "\\end{table}\n";
        /*
            s +=    "%wykres gantt'a\n"
                   "\t\\begin{figure}[htb]\n"
                   "\t\t\\centering\n"
                   "\t\t\\def\\svgwidth{\\columnwidth}\n"
                   "\t\t\\input{";
            s +=    pdfName + "_tex}\n"
                    "\t\t\\caption{Wykres Gantt'a}\n"
                    "\t\\end{figure}\n"
                    "\t\\FloatBarrier\n";
        */
        m_summary = new QString(s);
    }

    return *m_summary;
}

const QList<QString> &Chromosome::genes() const
{
    return m_genes;
}

void Chromosome::calculateValues()
{
    int jobsCount = Jobshop::instance()->jobCount();
    const QList<Job>& jobs = Jobshop::instance()->jobs();

    //kiedy konczy sie poprzednia operacjia zadania
    QVector<int> jobTime;
    //na poczatku czas przyjecia zadania
    jobTime.resize(jobsCount);
    for(int i=0; i<jobsCount; ++i)
        jobTime[i] = jobs[i].arrival();

    //kiedy konczy sie poprzednia operacja maszyny
    QVector<int> machineTime(Jobshop::instance()->machinesCount(), 0);

 //   qDebug() << "op.id()" << "jt" << "mt" << "start" << "op.time()" << "end";
    for(const QString& gene : m_genes)
    {
        const Operation& op = Jobshop::instance()->operation(gene);
        int& jt = jobTime[op.jobNumber()];
        int& mt = machineTime[op.machine()];
        int start = std::max<int>(jt, mt);
        m_operationsStartTime.insert(op.id(), start);
        int end = start + op.time();
  //      qDebug() << op.id() << jt << mt << start << op.time() << end;
        jt = end;
        mt = end;
    }

    m_meanTardy = 0;
    m_meanFlow = 0;
    m_numberOfTardy = 0;
    double sum = 0;
    m_valueAlpha = 0;
    for(int i=0; i<jobsCount; ++i)
    {
        const Job& job = jobs[i];
        Result result(job.id(), jobTime[i], job.dueDate(), job.arrival());
        m_results.append(result);

        sum += pow(result.lateness(), 2);
        sum += pow(result.earliness(), 2);

        m_valueAlpha += result.earliness() * job.alpha();
        m_valueAlpha += result.lateness() * job.beta();

        m_meanFlow += result.flow();

        if(result.lateness() > 0)
            ++m_numberOfTardy;
        m_meanTardy += double(result.lateness());
    }

    m_meanTardy /= (double)jobsCount;

    m_meanFlow /= jobsCount;
    m_valueMean = std::sqrt(sum);
}

void Chromosome::addGene(const QString &gene)
{
    m_genes.append(gene);
}

QString Chromosome::print() const
{
    QString x;
    for(int i=0; i < m_genes.count(); ++i)
    {
        x += m_genes[i];
        x += " ";
    }
    x.append(QString("valueMean: %1 valueAlpha: %2").arg(m_valueMean).arg(m_valueAlpha));
    return x;
}

QList<Chromosome> MSX(const Chromosome &a, const Chromosome &b)
{
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution(1,2);

    QList<QString> merge;

    auto p1 = a.m_genes.begin();
    auto p2 = b.m_genes.begin();

    auto end1 = a.m_genes.end();
    auto end2 = b.m_genes.end();

    while(p1 != end1 || p2!= end2)
    {
        int roll = distribution(Jobshop::instance()->rng());

        if(p2 != end2 && (p1 == end1 || roll == 2))
        {
            merge.append(*p2);
            ++p2;
        }
        else if(p1 != end1 && (p2 == end2 || roll == 1))
        {
            merge.append(*p1);
            ++p1;
        }
        else
            qWarning() << "out of range?";
    }

    Chromosome c1;
    Chromosome c2;

    for(QList<QString>::iterator it = merge.begin(); it != merge.end(); ++it)
    {
        if(!c1.hasGene(*it))
            c1.addGene(*it);
        else
            c2.addGene(*it);
    }

    c1.calculateValues();
    c2.calculateValues();

    return QList<Chromosome>() << c1 << c2;
}

QDebug operator<<(QDebug d, const Chromosome &chromosome)
{
    int count = chromosome.m_genes.count();
    for(int i=0; i < count; ++i)
        d << chromosome.m_genes[i];
    d << "| valueMean:" << chromosome.m_valueMean << "valueAlpha:" << chromosome.m_valueAlpha;
    return d;
}

/*
void ResultWindow::pdf(const QString &fileName)
{
    const QString texFile("output/wrapped.tex");

    this->latex("output/temp.tex");

    QString s;
    s =     "\\documentclass[11pt,a4paper]{article}\n"
            "\\usepackage{polski}\n" //[babel]
            "\\usepackage[utf8]{inputenc}\n"
            "\\usepackage{mathtools}\n"
            "\\usepackage{color}\n"
            "\\usepackage{graphicx}\n"
            "\\usepackage{lscape}\n"
            "\\usepackage{transparent}\n"
            "\\mathtoolsset{showonlyrefs}\n"
            "\\title{Generated by kSzereg}\n"
            "\\date{}\n"
            "\\begin{document}\n"
            "\t\\input{";
    s +=    "temp.tex";
    s +=    "}\n"
            "\\end{document}\n";

    save(texFile, s);

    QStringList args;
    args << "--pdf" << "--inplace" << "-I" << "output" << texFile;
    run("rubber", args);

    args.clear();
    args << "--clean" << "--inplace" << texFile;
    run("rubber", args);

    QDir::current().rename("output/wrapped.pdf", fileName);
}
*/
