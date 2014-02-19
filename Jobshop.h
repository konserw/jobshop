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
 * \brief The Jobshop class - holds information about problem to solve.
 * Implemented using singleton design pattern
 */
class Jobshop : public QObject
{
    Q_OBJECT

public:
    enum FitnessFunction
    {
        SquareMean,
        AlphaBeta
    };

    ///Destructor - empty, placeholder
    ~Jobshop();
    /*!
     * \brief instance Used to acquire only instance of Jobshop class and creates one if doesn't exist already
     * \return Pointer to only instance of Jobshop class
     */
    static Jobshop* instance();
    /*!
     * \brief instance Used to acquire instance of JobshopModel class bound to this object and creates one if doesn't exist already
     * \return Pointer to instance of JobshopModel class
     */
    JobshopModel* model();

    /*!
     * \brief insertOperation inserts new Operation into operations base
     * \param color Color that all operations in one job share in Gantt chart
     * \param id Operation's id
     */
    void insertOperation(const QColor& color, const QString& id);
    /*!
     * \brief operation Getter of Operation object. Flyweight pattern (?)
     * \param id of operation to be returned
     * \return reference to Operation object that corresponds to given id
     */
    Operation &operation(const QString& id);
    /*!
     * \brief removeOperation Used to delete Operation object
     * \param id of Operation to be removed
     */
    void removeOperation(const QString& id);

    /*!
     * \brief Getter of random nubers generator
     * \return Reference to the random numbers generator
     */
    std::mt19937& rng();

    /*!
     * \brief Getter of jobs list
     * \return Const reference to jobs list
     */
    const QList<Job>& jobs() const;

public slots:
    FitnessFunction fitnessFunction() const;
    void setFitnessFunction(FitnessFunction fitnessFunction);

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

    /*!
     * \brief load - deserialize instance from QDataStream.
     * Warning! there is no check if datastream contains proper instance of Jobshop
     * \param in datastream from where serialized instance is read
     */
    void load(QDataStream &in);
    /*!
     * \brief save - Serializes this instance
     * \param out datastream to which serialization is done
     */
    void save(QDataStream &out);

    ///Generate Jobshop sceduling problem randomly.
    void demodata();

    ///Initialize genome witch random, but valid (in sense of jobshop problem constraints) Chromosomes
    void generateInitialPopulation();
    ///Performs one full iteration - reproduction, reinsertion and succesion
    void iteration();

    ///Returns current best chromosome
    const Chromosome& winner() const;
    ///Returns chromosome constructed by FIFO cheuristic
    Chromosome fifo() const;
    ///Returns chromosome constructed by FIFO cheuristic
    Chromosome lifo() const;

signals:
    /*!
     * \brief iterationResult - signal emited after each iteration
     * \param low worst Chromosome fitness function value
     * \param hi best Chromosem fitness function value
     */
    void iterationResult(double low, double hi);

protected:
    ///Default constructor, used only by instance()
    Jobshop();
    ///Pointer to only instance of this class
    static Jobshop* m_instance;
    ///Object responsible for interaction with GUI
    JobshopModel* m_model;

    ///Conduct reproduction using MSX recombination
    virtual void reproduce();
    ///printGenome - used for printing current genome to log file
    void printGenome() const;

    ///Number of machines used by operations
    int m_machinesCount;
    ///Number of operations each job contains
    int m_operationsCount;
    ///Number of Chromosome objects in genome
    int m_population;
    ///Number of crossover operations per iteration, offspring = crossovers*2
    int m_crossovers;
    ///Current iteration number
    int m_iteration;

    ///List containing Job objects
    QList<Job> m_jobs;
    ///Hash mapping operation id to Operation object
    QHash<QString, Operation> m_operations;
    ///List conaining current population of Chromosome objects
    QList<Chromosome> m_chromosomes;

    ///Random numbers generator for MSX and initial population generation
    std::mt19937 m_rng;

    FitnessFunction m_fitnessFunction;

    friend class JobshopModel;
};


#endif // JOBSHOP_H
