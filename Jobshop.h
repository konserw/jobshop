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

    std::mt19937& rng();

    QList<Job> jobs() const;

public slots:
    int crossovers() const;
    void setCrossovers(int crossovers);

    int population() const;
    void setPopulation(int population);

    void addJobs(int count);
    void removeJobs(int count);
    int jobCount() const;

    int machinesCount() const;
    void setMachinesCount(int machinesCount);

    int operationsCount() const;
    void setOperationsCount(int operationsCount);
    int allOperationsCount() const;

    void load(QDataStream &in);
    void save(QDataStream &out);
    void solve();

signals:
    void iteration(double low, double hi);

protected:
    Jobshop();
    static Jobshop* m_instance;

    JobshopModel* m_model;
    QList<Job> m_jobs;

    QHash<QString, Operation> m_operations;

    int m_machinesCount;
    int m_operationsCount;

    QList<Chromosome> m_genome;

    int m_population;
    static const int m_iterationCount = 50;//m_chromosomeCount;
    int m_crossovers; //number of offspring = cycles*2

    std::mt19937 m_rng;

    void generateInitialPopulation();
    QList<Chromosome> reproduce();

    friend class JobshopModel;
};


#endif // JOBSHOP_H
