#include "Jobshop.h"
#include "JobshopModel.h"
#include "Operation.h"

#include <QVector>
#include <algorithm>
#include <QtDebug>
#include <cmath>
#include <ctime>
#include <QtAlgorithms>

Jobshop* Jobshop::m_instance = nullptr;

Jobshop::Jobshop()
    : m_operationsCount(0),
      m_machinesCount(1),
      m_model(nullptr),
      m_fitnessFunction(Jobshop::SquareMean)
{
    m_rng.seed(time(NULL));
}

void Jobshop::printGenome() const
{
    for(const Chromosome& ch : m_genome)
        qDebug() << ch;
}

Jobshop::FitnessFunction Jobshop::fitnessFunction() const
{
    return m_fitnessFunction;
}

void Jobshop::setFitnessFunction(FitnessFunction fitnessFunction)
{
    m_fitnessFunction = fitnessFunction;
}


int Jobshop::population() const
{
    return m_population;
}

void Jobshop::setPopulation(int population)
{
    m_population = population;
}

int Jobshop::crossovers() const
{
    return m_crossovers;
}

void Jobshop::setCrossovers(int crossovers)
{
    m_crossovers = crossovers;
}

const QList<Job> &Jobshop::jobs() const
{
    return m_jobs;
}

std::mt19937& Jobshop::rng()
{
    return m_rng;
}

void Jobshop::load(QDataStream &in)
{
    m_operations.clear();
    m_jobs.clear();

    qint64 operations;
    qint64 machines;
    qint64 jobs;
    qint64 cross;
    qint64 population;

    in  >> operations
        >> machines
        >> jobs
        >> cross
        >> population;

    m_operationsCount = operations;
    m_machinesCount = machines;

    m_crossovers = cross;
    m_population = population;

    for(qint64 i=0; i<jobs; ++i)
    {
        Job job;
        in >> job;
        m_jobs.append(job);
    }

    for(Job& job : m_jobs)
        qDebug() << "job" << job.id() << "ids:" << job.m_operationIds;

    for(qint64 i=0; i<operations*jobs; ++i)
    {
        Operation op;
        in >> op;
        m_operations.insert(op.id(), op);
    }

    qDebug() << "operations" << m_operations.keys();
}

void Jobshop::save(QDataStream &out)
{
    qint64 operations = qint64(m_operationsCount);
    qint64 machines = qint64(m_machinesCount);
    qint64 jobs = qint64(m_jobs.count());

    qint64 cross = qint64(m_crossovers);
    qint64 populaiton = qint64(m_population);

    out << operations
        << machines
        << jobs
        << cross
        << populaiton;

    for(const Job& j : m_jobs)
        out << j;

    for(const Operation& op : m_operations)
        out << op;
}

int Jobshop::allOperationsCount() const
{
    return m_operations.count();
}

Jobshop::~Jobshop()
{
}

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
    m_genome.clear();
    m_iteration = 0;

    qDebug() << "Problem parameters:";
    for(const Job& j : m_jobs)
        qDebug() << j.print();

    int jobsCount = m_jobs.count();
    std::uniform_int_distribution<int> dist(0, jobsCount-1);

    for(int i=0; i < m_population; ++i)
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
        x.calculateValues();
        m_genome.append(x);
    }
    qSort(m_genome);

    qDebug() << "Initial population";
    printGenome();
}

void Jobshop::reproduce()
{
    std::uniform_int_distribution<int> dist(0, m_genome.count()-1);
    QList<Chromosome> offspring;
    for(int i=0; i<m_crossovers; ++i)
    {
        //todo losowanie parentow wg rankingu
        offspring.append(MSX(m_genome[dist(m_rng)], m_genome[dist(m_rng)]));
    }

    m_genome.append(offspring);
}

void Jobshop::iteration()
{
    reproduce();

    qSort(m_genome);

    while(m_genome.count() > m_population)
        m_genome.removeLast();

    qDebug() << "Iteration:\t" << ++m_iteration;
    printGenome();

    emit iterationResult(m_genome.last().value(), m_genome[0].value());
}

const Chromosome &Jobshop::winner() const
{
    return m_genome.first();
}

Chromosome Jobshop::fifo() const
{
    //kiedy konczy sie poprzednia operacja maszyny
    QVector<int> machineTime(m_machinesCount, 0);

    int jobsCount = m_jobs.count();
    //current operation of each job
    QVector<int> currentOperationOfJob(jobsCount, 0);

    //kiedy konczy sie poprzednia operacjia zadania
    QVector<int> jobTime;
    //na poczatku czas przyjecia zadania
    jobTime.resize(jobsCount);
    for(int i=0; i<jobsCount; ++i)
        jobTime[i] = m_jobs[i].arrival();

    Chromosome chromosome;
    int t=0;

    while(1)
    {
        bool endFlag = true;
        for(int jobNumber=0; jobNumber<jobsCount; ++jobNumber)
        {
            int& opNum = currentOperationOfJob[jobNumber];
            if(opNum > m_operationsCount)
                continue;

            endFlag = false;

            int& jt = jobTime[jobNumber];
            if(t >= jt)
            {
                const Operation& op = m_jobs[jobNumber].operation(opNum);

                int& mt = machineTime[op.machine()];
                int start = std::max<int>(jt, mt);
                int end = start + op.time();
                jt = end;
                mt = end;

                chromosome.addGene(op.id());
                ++opNum;
            }
        }
        if(endFlag)
            break;
        ++t;
    }

    chromosome.calculateValues();
    qDebug() << "FIFO:" << chromosome;
    return chromosome;
}

Chromosome Jobshop::lifo() const
{
    //kiedy konczy sie poprzednia operacja maszyny
    QVector<int> machineTime(m_machinesCount, 0);

    int jobsCount = m_jobs.count();
    //current operation of each job
    QVector<int> currentOperationOfJob(jobsCount, 0);
    //is job active
    QVector<bool> isJobActive(jobsCount, true);
    //kiedy konczy sie poprzednia operacjia zadania
    QVector<int> jobTime;
    //na poczatku czas przyjecia zadania
    jobTime.resize(jobsCount);
    for(int i=0; i<jobsCount; ++i)
        jobTime[i] = m_jobs[i].arrival();

    QVector<QList<QString> > queues(m_machinesCount);

    Chromosome chromosome;
    int t=0;

    while(1)
    {
        for(int jobNumber=0; jobNumber<jobsCount; ++jobNumber)
        {
            if(!isJobActive[jobNumber])
                continue;

            int& jt = jobTime[jobNumber];
            if(t >= jt)
            {
                const Operation& op = m_jobs[jobNumber].operation(currentOperationOfJob[jobNumber]);
                isJobActive[jobNumber] = false;
                queues[op.machine()].append(op.id());
            }
        }

        for(int machineNumber=0; machineNumber<m_machinesCount; ++machineNumber)
        {
            int& mt = machineTime[machineNumber];
            QList<QString>& q = queues[machineNumber];
            if(t >= mt && !q.isEmpty())
            {
                const Operation& op = m_operations[q.last()];
                int jn = op.jobNumber();

                int end = mt + op.time();
                mt = end;
                jobTime[jn] = end;

                q.removeLast();
                chromosome.addGene(op.id());

                if(currentOperationOfJob[jn]++ < m_operationsCount)
                    isJobActive[jn] = true;
            }
        }

        if(chromosome.geneCount() == m_genome.count())
            break;
        ++t;

  //      qDebug() << "t:" << t << "gene count:" << chromosome.geneCount() << "/" <<  m_genome.count();
    }

    chromosome.calculateValues();
    qDebug() << "LIFO:" << chromosome;
    return chromosome;
}

void Jobshop::demodata()
{
    qsrand(time(0));

    for(Operation& op : m_operations)
    {
        op.setMachine(qrand() % m_machinesCount);
        op.setTime(qrand() % 15 + 1);
    }
    int i=0;
    for(Job& job : m_jobs)
    {
        double r = qrand()%100;
        r /= 100;
        job.setAlpha(r);
        job.setBeta(1-r);
        job.setArrival(qrand()%50);
        job.setDueDate(job.totalTime()*2.5);
        job.setName(QString("%1. job").arg(++i));
    }
}

void Jobshop::addJobs(int count)
{
    for(int i=0; i<count; ++i)
        m_jobs.append(Job(m_operationsCount));
    
}

void Jobshop::removeJobs(int count)
{
    for(int i=0; i<count; ++i)
        m_jobs.removeLast();
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
    for(Job& job : m_jobs)
        job.setOperationsCount(operationsCount);

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
