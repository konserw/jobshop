#include "JobshopModel.h"
#include "Job.h"

#include <QDataStream>
#include <QtDebug>
#include <QVariant>

JobshopModel::JobshopModel(QObject *parent)
    : QAbstractTableModel(parent),
      m_operationsCount(0)
{

}

JobshopModel::~JobshopModel()
{
    qDeleteAll(m_jobs);
}

bool JobshopModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return true;
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
        return section - 3;
    }
}

QModelIndex JobshopModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

int JobshopModel::rowCount(const QModelIndex &parent) const
{
    return m_jobs.count();
}

QVariant JobshopModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !(role == Qt::DisplayRole || role  == Qt::EditRole))
        return QVariant();

    Job* job = m_jobs[index.row()];

    return job->data(index.column());
}

void JobshopModel::addJob()
{
    int row = m_jobs.count();
    beginInsertRows(QModelIndex(), row, row);
    m_jobs.append(new Job());
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

void JobshopModel::setMachinesCount(const qint32 &machinesCount)
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
