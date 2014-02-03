#include "Chromosome.h"
#include "Jobshop.h"

Chromosome::Chromosome()
{
}

bool Chromosome::hasGene(const QString &gene)
{
    return m_genes.contains(gene);
}

double Chromosome::value() const
{
    //todo
    return 0;
}

void Chromosome::addGene(const QString &gene)
{
    m_genes.append(gene);
}

QString Chromosome::print() const
{
    QString x;
    for(int i=0; i < m_genes.count(); ++i)
    {
        x += m_genes[i];
        x += " ";
    }
    return x;
}

