#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <QHash>
#include <QList>
#include <QString>
#include "Result.h"

/*!
 * \brief The Chromosome class - represnts single schedule as order of operations (genes)
 */
class Chromosome
{
public:
    Chromosome();

    int geneCount() const;

    bool hasGene(const QString& gene) const;
    void addGene(const QString& gene);

    QString print() const;

    /*!
     * \brief Based on Jobshop::instance()->fitnessFunction() returns value of proper fitness function
     * calculateValues() must be called before this method in order to evaluate all fitness functions values
     * \return Value of fitness function.
     */
    double value() const;
    ///value of fitness funciton meanSquare
    double valueMean() const;
    ///value of fitness function alphaBeta
    double valueAlpha() const;
    ///Calculate all statistics
    void calculateValues();

    ///Completion time of all operations
    int completionTime() const;
    ///Mean flow time
    double meanFlow() const;
    ///Number of tardy(late) jobs
    int tardy() const;
    ///Maximum tardiness
    int maxTardy() const;

    //for sorting
    bool operator<(const Chromosome& other) const;
    bool operator>(const Chromosome& other) const;

    const QList<Result>& results() const;

    ///Returns scheduled start time for operation in this chromosome (schedule)
    int startTime(const QString& operation) const;

protected:
    ///value of fitness funciton meanSquare
    double m_valueMean;
    ///value of fitness function alphaBeta
    double m_valueAlpha;
    ///Number of tardy (late) jobs
    int m_numberOfTardy;
    ///Mean flow time
    double m_meanFlow;

    ///Basic statistics for each job
    QList<Result> m_results;
    ///String representation of chromosome - sequence of operation IDs
    QList<QString> m_genes;
    ///Starting time for each operation
    /// Externistic state in flyweight design pattern
    QHash<QString, int> m_operationsStartTime;

    friend QDebug& operator<< (QDebug& d, const Chromosome& chromosome);
    friend QList<Chromosome> MSX(const Chromosome& a, const Chromosome& b);
};

QList<Chromosome> MSX(const Chromosome& a, const Chromosome& b);

QDebug& operator<< (QDebug& d, const Chromosome& chromosome);

#endif // CHROMOSOME_H
