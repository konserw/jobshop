#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <QList>
#include <QString>

class Operation;

/*!
 * \brief The Chromosome class - represnts single schedule as order of operations (genes)
 */
class Chromosome
{
public:
    Chromosome();

    bool hasGene(const QString& gene);
    ///value of survival funciton
    double value() const;
    void calculateValue();

    void addGene(const QString& gene);

    QString print() const;

    bool operator<(const Chromosome& other) const;

protected:
    double m_value;
    QList<QString> m_genes;

    friend QList<Chromosome> MSX(const Chromosome& a, const Chromosome& b);
};

QList<Chromosome> MSX(const Chromosome& a, const Chromosome& b);

#endif // CHROMOSOME_H
