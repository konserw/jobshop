#include "Chromosome.h"
#include "Jobshop.h"
#include "Job.h"
#include "Operation.h"

#include <QVector>
#include <random>
#include <algorithm>
#include <QtDebug>

Chromosome::Chromosome() :
    m_valueMean(-1),
    m_valueAlpha(-1)
{
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

    for(const QString& gene : m_genes)
    {
        const Operation& op = Jobshop::instance()->operation(gene);
        int& jt = jobTime[op.jobNumber()];
        int& mt = machineTime[op.machine()];
        int start = std::max<int>(jt, mt);
        m_operationsStartTime.insert(op.id(), start);
        int end = start + op.time();
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

QDebug& operator<<(QDebug& d, const Chromosome &chromosome)
{
    int count = chromosome.m_genes.count();
    for(int i=0; i < count; ++i)
        d << chromosome.m_genes[i];
    d << "| valueMean:" << chromosome.m_valueMean << "valueAlpha:" << chromosome.m_valueAlpha;
    return d;
}

