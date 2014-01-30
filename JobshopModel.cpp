#include "JobshopModel.h"
#include "Jobshop.h"
#include "Job.h"
#include "Operation.h"

#include <QDataStream>
#include <QtDebug>
#include <QVariant>

JobshopModel::JobshopModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

JobshopModel::~JobshopModel()
{
}

bool JobshopModel::setData(const QModelIndex &index, const QVariant &value, int /*role*/)
{
    /*
    if(role != Qt::EditRole || index.row() >= m_jobs.count())
        return false;
*/
    Job& job = Jobshop::instance()->m_jobs[index.row()];

    switch(index.column())
    {
    case 0:
        job.setName(value.toString());
        return true;
    case 1:
        job.setArrival(value.toInt());
        return true;
    case 2:
        job.setDueDate(value.toInt());
        return true;
    case 3:
        job.setAlpha(value.toDouble());
        return true;
    case 4:
        job.setBeta(value.toDouble());
        return true;
    default:
        job.setOperation(index.column() - m_nonOperationColumns, qvariant_cast<Operation>(value));
        return true;
    }
}

Qt::ItemFlags JobshopModel::flags(const QModelIndex &/*index*/) const
{
    return Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled;
}

QVariant JobshopModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Vertical)
        return section + 1;

    switch(section)
    {
    case 0:
        return tr("Nazwa zlecenia");
    case 1:
        return tr("Czas rozpoczęcia");
    case 2:
        return tr("Czas zakończenia");
    case 3:
        return tr("α");
    case 4:
        return tr("β");
    default:
        return section - m_nonOperationColumns + 1;
    }
}

bool JobshopModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+count-1);
    //naything here?
    endInsertRows();
    return true;
}
/*
QModelIndex JobshopModel::index(int row, int column, const QModelIndex &parent) const
{
    if(column >= (m_nonOperationColumns + m_operationsCount) || row >= m_jobs.count())
        return QModelIndex();

    if(column < m_nonOperationColumns)
        return createIndex(row, column);

    return createIndex(row, column, m_jobs[row]->operation(column - m_nonOperationColumns));
}
*/
int JobshopModel::rowCount(const QModelIndex &/*parent*/) const
{
    return Jobshop::instance()->m_jobs.count();
}

QVariant JobshopModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !(role == Qt::DisplayRole || role  == Qt::EditRole))
        return QVariant();

    const Job& job = Jobshop::instance()->m_jobs[index.row()];

    switch(index.column())
    {
    case 0:
        return job.name();
    case 1:
        return job.arrival();
    case 2:
        return job.dueDate();
    case 3:
        return job.alpha();
    case 4:
        return job.beta();
    default:
        if(role == Qt::DisplayRole)
            return job.operation(index.column() - m_nonOperationColumns).print();
        return QVariant::fromValue(job.operation(index.column() - m_nonOperationColumns));
    }
}

int JobshopModel::nonOperationColumns()
{
    return m_nonOperationColumns;
}

int JobshopModel::columnCount(const QModelIndex & /*parent*/) const
{
    return m_nonOperationColumns + Jobshop::instance()->m_operationsCount;
}

bool JobshopModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);
    //naything here?
    endRemoveRows();
    return true;
}

bool JobshopModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column+count-1);
    //naything here?
    endInsertColumns();
    return true;
}

bool JobshopModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column+count-1);
    //naything here?
    endRemoveColumns();
    return true;
}
