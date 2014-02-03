#ifndef JOBSHOP_H
#define JOBSHOP_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QMap>
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

public slots:
    void solve();

    void addJob();
    //    void addJob(Job *job);
    //void clear();

    int machinesCount() const;
    void setMachinesCount(int machinesCount);

    int operationsCount() const;
    void setOperationsCount(int operationsCount);

    void generateInitialPopulation();

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

    QMap<double, Chromosome> m_genome;

    static const int m_iterationCount = 100;
    static const int m_chromosomeCount = 20;

    std::mt19937 m_rng;

    friend class JobshopModel;
};


#endif // JOBSHOP_H
