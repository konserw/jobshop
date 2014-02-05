#include "Jobshop.h"
#include "JobshopModel.h"
#include "Operation.h"

#include <QtDebug>
#include <cmath>
#include <ctime>
#include <QtAlgorithms>

Jobshop* Jobshop::m_instance = nullptr;

Jobshop::Jobshop()
    : m_operationsCount(0),
      m_machinesCount(1),
      m_model(nullptr)
{
    m_rng.seed(time(NULL));
}

QList<Job> Jobshop::jobs() const
{
    return m_jobs;
}

std::mt19937& Jobshop::rng()
{
    return m_rng;
}

void Jobshop::load(QDataStream &in)
{
    m_jobs.clear();

    qint64 operations;
    qint64 machines;
    qint64 jobs;

    in  >> operations
        >> machines
        >> jobs;

    m_operationsCount = operations;
    m_machinesCount = machines;

    for(qint64 i=0; i<operations*jobs; ++i)
    {
        Operation op;
        in >> op;
        m_operations.insert(op.id(), op);
    }

    for(qint64 i=0; i<jobs; ++i)
    {
        Job job;
        in >> job;
        m_jobs.append(job);
    }
}

void Jobshop::save(QDataStream &out)
{
    qint64 operations = qint64(m_operationsCount);
    qint64 machines = qint64(m_machinesCount);
    qint64 jobs = qint64(m_jobs.count());

    out << operations
        << machines
        << jobs;

    for(const Operation& op : m_operations)
    {
        out << op;
    }

    for(qint32 i=0; i<jobs; ++i)
    {
        out << m_jobs[i];
    }
}

int Jobshop::allOperationsCount() const
{
    return m_operations.count();
}

Jobshop::~Jobshop()
{ qDebug() << "destroy singleton"; }

Jobshop *Jobshop::instance()
{
    if(m_instance == nullptr)
        m_instance = new Jobshop;
    return m_instance;
}

JobshopModel *Jobshop::model()
{
    if(m_model == nullptr)
        m_model = new JobshopModel(this);
    return m_model;
}

Operation& Jobshop::operation(const QString &id)
{
    if(!m_operations.contains(id))
        m_operations.insert(id, Operation(id));

    return m_operations[id];
}

void Jobshop::removeOperation(const QString &id)
{
    m_operations.remove(id);
}

void Jobshop::generateInitialPopulation()
{
    int jobsCount = m_jobs.count();
    std::uniform_int_distribution<int> dist(0, jobsCount-1);

    for(int i=0; i < m_chromosomeCount; ++i)
    {
        Chromosome x;
        QVector<int> operationsFrom(jobsCount, 0);
        bool anyLeft = true;
        do
        {
            int jobNumber = dist(m_rng);
            if(operationsFrom[jobNumber] < m_operationsCount)
            {
                x.addGene(QString("%1%2")
                          .arg(QString('A' + jobNumber))
                          .arg(operationsFrom[jobNumber])
                          );
                operationsFrom[jobNumber] = operationsFrom[jobNumber] + 1;
            }
            else
            {
                anyLeft = false;
                std::for_each(
                        operationsFrom.begin(),
                        operationsFrom.end(),
                        [&](int n){ anyLeft = anyLeft || n < m_operationsCount; }
                );
            }
        }while(anyLeft);
        x.calculateValue();
        m_genome.append(x);
        qDebug() << x.print();
    }
}

QList<Chromosome> Jobshop::reproduce()
{
    std::uniform_int_distribution<int> dist(0, m_genome.count()-1);
    QList<Chromosome> offspring;
    for(int i=0; i<m_reproductionCycles; ++i)
    {
        //todo losowanie parentow wg rankingu
        offspring.append(MSX(m_genome[dist(m_rng)], m_genome[dist(m_rng)]));
    }

    return offspring;
}


void Jobshop::solve()
{
    qDebug() << "Problem parameters:";
    for(const Job& j : m_jobs)
        qDebug() << j.print();

    qDebug() << "Initial population";
    generateInitialPopulation();
    qSort(m_genome);
    qDebug() << "best value:" << m_genome[0].value();
    qDebug() << "worst value:" << m_genome.last().value();

    for(int i=0; i<m_iterationCount; ++i)
    {
        m_genome.append(reproduce());
        qSort(m_genome);
        while(m_genome.count() > m_chromosomeCount)
            m_genome.removeLast();

        qDebug() << "Iteration:\t" << i+1;
        qDebug() << "best value:" << m_genome[0].value();
        qDebug() << "worst value:" << m_genome.last().value();
    }
}

void Jobshop::addJob()
{
    int row = m_jobs.count();
    m_jobs.append(Job(m_operationsCount));
    m_model->insertRow(row);
}

int Jobshop::jobCount() const
{
    return m_jobs.count();
}

int Jobshop::operationsCount() const
{
    return m_operationsCount;
}

void Jobshop::setOperationsCount(int operationsCount)
{
    int diff = operationsCount - m_operationsCount; //number of columns to be added
    if(!diff) //no change
        return;

    for(Job& job : m_jobs)
        job.setOperationsCount(operationsCount);

    if(diff > 0)//adding rows
        m_model->insertColumns(m_operationsCount, diff);
    else
        m_model->removeColumns(operationsCount, std::abs(diff));

    m_operationsCount = operationsCount;
}

int Jobshop::machinesCount() const
{
    return m_machinesCount;
}

void Jobshop::setMachinesCount(int machinesCount)
{
    m_machinesCount = machinesCount;
}
