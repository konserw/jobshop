#ifndef JOBSHOP_H
#define JOBSHOP_H

#include <QObject>
#include <QList>
#include <QHash>
#include <random>

#include "Chromosome.h"
#include "Job.h"


class JobshopModel;
class Operation;

/*!
 * \brief The Jobshop class - holds information about problem to solve. Implemented as singleton
 */
class Jobshop : public QObject
{
    Q_OBJECT

public:
    ~Jobshop();
    static Jobshop* instance();

    JobshopModel* model();

    Operation &operation(const QString& id);
    void removeOperation(const QString& id);

    std::mt19937 rng() const;

    QList<Job> jobs() const;

public slots:
    void solve();

    void addJob();
    int jobCount() const;
    //    void addJob(Job *job);
    //void clear();

    int machinesCount() const;
    void setMachinesCount(int machinesCount);

    int operationsCount() const;
    void setOperationsCount(int operationsCount);
    int allOperationsCount() const;

    void load(QDataStream &in);
    void save(QDataStream &out);


protected:
    Jobshop();
    static Jobshop* m_instance;

    JobshopModel* m_model;
    QList<Job> m_jobs;

    QHash<QString, Operation> m_operations;

    int m_machinesCount;
    int m_operationsCount;

    QList<Chromosome> m_genome;

    static const int m_chromosomeCount = 12;
    static const int m_iterationCount = m_chromosomeCount;
    static const int m_reproductionCycles = m_chromosomeCount/4;

    std::mt19937 m_rng;

    void generateInitialPopulation();
    QList<Chromosome> reproduce();

    friend class JobshopModel;
};


#endif // JOBSHOP_H
