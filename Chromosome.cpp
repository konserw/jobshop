#include "Chromosome.h"
#include "Jobshop.h"

#include <random>

Chromosome::Chromosome()
    : m_value(-1)
{
}

bool Chromosome::hasGene(const QString &gene)
{
    return m_genes.contains(gene);
}

double Chromosome::value() const
{
    return m_value;
}

void Chromosome::calculateValue()
{
    //todo
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

bool Chromosome::operator<(const Chromosome &other) const
{
    return m_value < other.m_value;
}

QList<Chromosome> MSX(const Chromosome &a, const Chromosome &b)
{
    static std::uniform_int_distribution<int> dist(0,1);

    int opc = Jobshop::instance()->allOperationsCount() * 2;
    QList<QString> merge;
    QList<QString>::const_iterator p1 = a.m_genes.begin();
    QList<QString>::const_iterator p2 = b.m_genes.begin();

    for(int i = 0; i < opc; ++i)
    {
        if(p1 != a.m_genes.end() &&
           (dist(Jobshop::instance()->rng()) == 0 || p2 == b.m_genes.end())
        ){
            merge.append(*p1);
            ++p1;
        }
        else
        {
            merge.append(*p2);
            ++p2;
        }
    }

    Chromosome c1;
    Chromosome c2;

    for(QList<QString>::iterator it = merge.begin(); it != merge.end(); ++it)
    {
        if(!c1.hasGene(*it))
            c1.addGene(*it);
        else
            c2.addGene(*it);
    }

    c1.calculateValue();
    c2.calculateValue();

    return QList<Chromosome>() << c1 << c2;
}
