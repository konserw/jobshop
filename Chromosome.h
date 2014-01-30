#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <QList>

class Operation;

/*!
 * \brief The Chromosome class - represnts single schedule as order of operations (genes)
 */
class Chromosome
{
public:
    Chromosome();

    bool hasOperation(const Operation& Operation);
    double value();

protected:
    QList<Operation> m_operations;

};

#endif // CHROMOSOME_H
