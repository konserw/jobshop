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

    void addGene(const QString& gene);

    QString print() const;

protected:
    QList<QString> m_genes;

};

#endif // CHROMOSOME_H
