#include "Chromosome.h"
#include "Jobshop.h"
#include "Job.h"
#include "Operation.h"

#include <QVector>
#include <random>
#include <algorithm>
#include <QtDebug>

Chromosome::Chromosome()
    : m_value(-1)
{
}

bool Chromosome::hasGene(const QString &gene)
{
    return m_genes.contains(gene);
}

double Chromosome::value() const
{
    return m_value;
}

int Chromosome::completionTime() const
{
    auto r = std::max_element(m_results.begin(), m_results.end(), comparecompletionTime);
    return r->cj();
}

bool Chromosome::operator<(const Chromosome& other) const
{
    return m_value < other.m_value;
}

bool Chromosome::operator>(const Chromosome& other) const
{
    return m_value > other.m_value;
}

void Chromosome::calculateValue()
{
    int jobsCount = Jobshop::instance()->jobCount();
    const QList<Job>& jobs = Jobshop::instance()->jobs();

    //kiedy konczy sie poprzednia operacjia zadania
    QVector<int> jobTime;
    //na poczatku czas przyjecia zadania
    jobTime.clear();
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
        int end = start + op.time();
        jt = end;
        mt = end;
    }

    double sum = 0;
    for(int i=0; i<jobsCount; ++i)
    {
        const Job& job = jobs[i];
        Result r (i, jobTime[i], job.dueDate(), job.arrival());
        m_results.append(r);
        sum += pow(r.lj(), 2);
        sum += pow(r.ej(), 2);
    }

    m_value = std::sqrt(sum);
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
    x.append(QString("value: %1").arg(m_value));
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

    c1.calculateValue();
    c2.calculateValue();

    return QList<Chromosome>() << c1 << c2;
}

QDebug operator<<(QDebug d, const Chromosome &chromosome)
{
    d << chromosome.print();
    return d;
}
