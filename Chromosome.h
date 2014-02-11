#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <QList>
#include <QString>
#include "Result.h"

class Operation;

/*!
 * \brief The Chromosome class - represnts single schedule as order of operations (genes)
 */
class Chromosome
{
public:
    Chromosome();

    bool hasGene(const QString& gene);

    double value() const;
    void calculateValue();

    void addGene(const QString& gene);

    QString print() const;

    ///completion time of all operations
    int completionTime() const;
    ///mean flow time
    double meanFlow() const;

    //for sorting
    bool operator<(const Chromosome& other) const;
    bool operator>(const Chromosome& other) const;

    const QList<Result>& results() const;

protected:
    ///value of fitness funciton
    double m_value;

    ///Basic statistics for each job
    QList<Result> m_results;
    ///String representation of chromosome - sequence of operation IDs
    QList<QString> m_genes;

    friend QDebug operator<< (QDebug d, const Chromosome& chromosome);
    friend QList<Chromosome> MSX(const Chromosome& a, const Chromosome& b);
};

QList<Chromosome> MSX(const Chromosome& a, const Chromosome& b);

QDebug operator<< (QDebug d, const Chromosome& chromosome);

#endif // CHROMOSOME_H
