#include "Chromosome.h"
#include "Jobshop.h"
#include "Job.h"
#include "Operation.h"

#include <QVector>
#include <random>
#include <algorithm>

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
    static std::uniform_int_distribution<int> dist(0,1);

    int opc = Jobshop::instance()->allOperationsCount() * 2;
    QList<QString> merge;
    QList<QString>::const_iterator p1 = a.m_genes.begin();
    QList<QString>::const_iterator p2 = b.m_genes.begin();

    for(int i = 0; i < opc; ++i)
    {
        if(p1 != a.m_genes.end() &&
           (dist(Jobshop::instance()->rng()) == 0 || p2 == b.m_genes.end())
        ){
            merge.append(*p1);
            ++p1;
        }
        else
        {
            merge.append(*p2);
            ++p2;
        }
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
