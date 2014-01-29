#include "JobshopModel.h"
#include "Job.h"
#include "Operation.h"

#include <QDataStream>
#include <QtDebug>
#include <QVariant>

JobshopModel::JobshopModel(QObject *parent)
    : QAbstractTableModel(parent),
      m_operationsCount(0),
      m_machinesCount(1)
{
}

JobshopModel::~JobshopModel()
{
    qDeleteAll(m_jobs);
}

bool JobshopModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole || index.row() >= m_jobs.count())
        return false;

    Job* job = m_jobs[index.row()];

    switch(index.column())
    {
    case 0:
        job->setName(value.toString());
        return true;
    case 1:
        job->setArrival(value.toInt());
        return true;
    case 2:
        job->setDueDate(value.toInt());
        return true;
    case 3:
        job->setAlpha(value.toDouble());
        return true;
    case 4:
        job->setBeta(value.toDouble());
        return true;
    default:
        job->setOperation(index.column() - 5, qvariant_cast<Operation>(value));
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

QModelIndex JobshopModel::index(int row, int column, const QModelIndex &/*parent*/) const
{
    if(column >= (m_nonOperationColumns + m_operationsCount) || row >= m_jobs.count())
        return QModelIndex();

    if(column < m_nonOperationColumns)
        return createIndex(row, column);

    return createIndex(row, column, m_jobs[row]->operation(column - m_nonOperationColumns));
}

int JobshopModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_jobs.count();
}

QVariant JobshopModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !(role == Qt::DisplayRole || role  == Qt::EditRole))
        return QVariant();

    Job* job = m_jobs[index.row()];

    return job->data(index, role);
}

void JobshopModel::addJob()
{
    int row = m_jobs.count();
    beginInsertRows(QModelIndex(), row, row);
    m_jobs.append(new Job(m_operationsCount));
    endInsertRows();
}

void JobshopModel::addJob(Job* job)
{
    int row = m_jobs.count();
    beginInsertRows(QModelIndex(), row, row);
    m_jobs.append(job);
    endInsertRows();
}

void JobshopModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_jobs.count());
    qDeleteAll(m_jobs);
    m_jobs.clear();
    endRemoveRows();
}
qint32 JobshopModel::operationsCount() const
{
    return m_operationsCount;
}

void JobshopModel::setOperationsCount(const qint32 &operationsCount)
{
    if(m_operationsCount > operationsCount)
    {
        beginRemoveColumns(QModelIndex(), operationsCount, m_operationsCount-1);
        foreach(Job* job, m_jobs)
            job->setOperationsCount(operationsCount);
        endRemoveColumns();
    }
    else
    {
        beginInsertColumns(QModelIndex(), m_operationsCount+1, operationsCount);
        foreach(Job* job, m_jobs)
            job->setOperationsCount(operationsCount);
        endInsertColumns();
    }
    m_operationsCount = operationsCount;
}

int JobshopModel::nonOperationColumns()
{
    return m_nonOperationColumns;
}

qint32 JobshopModel::machinesCount() const
{
    return m_machinesCount;
}

void JobshopModel::setMachinesCount(int machinesCount)
{
    m_machinesCount = machinesCount;
}

int JobshopModel::columnCount(const QModelIndex & /*parent*/) const
{
    return m_nonOperationColumns + m_operationsCount;
}

QDataStream &operator <<(QDataStream &out, const JobshopModel &model)
{
    qint32 jobs = qint32(model.m_jobs.count());

    out << model.m_machinesCount                  //number of machines
        << model.m_operationsCount                //number of operations for each task
        << jobs;                                  //number of jobs

    for(qint32 i=0; i<jobs; ++i)
    {
        out << model.m_jobs[i];
    }
    return out;
}

QDataStream &operator >>(QDataStream &in, JobshopModel &model)
{
    qint32 jobs;

    in  >> model.m_machinesCount
        >> model.m_operationsCount
        >> jobs;

    Job* job;
    for(qint32 i=0; i<jobs; ++i)
    {
        job = new Job();
        in >> *job;
        model.addJob(job);
    }

    return in;
}
