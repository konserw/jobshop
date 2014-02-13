#include "ResultsModel.h"
#include <QtDebug>

ResultsModel::ResultsModel(const QList<Result> &results, QObject *parent) :
    QAbstractTableModel(parent),
    m_results(results)
{
}

QVariant ResultsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !(role == Qt::DisplayRole))
        return QVariant();

    const Result& res = m_results[index.row()];

    switch(index.column())
    {
    case 0:
        return res.completionTime();
    case 1:
        return res.flow();
    case 2:
        return res.lateness();
    case 3:
        return res.earliness();
    }

    qDebug() << "wrong index";
    return QVariant();
}

Qt::ItemFlags ResultsModel::flags(const QModelIndex &) const
{
    return Qt::ItemIsEnabled;
}

QVariant ResultsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Vertical)
        return m_results[section].jobID();

    switch(section)
    {
    case 0:
        return tr("Completion");
    case 1:
        return tr("Flow");
    case 2:
        return tr("Lateness");
    case 3:
        return tr("Earliness");
    }

    qDebug() << "wrong index";
    return QVariant();
}

int ResultsModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

int ResultsModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_results.count();
}
