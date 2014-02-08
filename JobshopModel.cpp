#include "JobshopModel.h"
#include "Jobshop.h"
#include "Job.h"
#include "Operation.h"

#include <QDataStream>
#include <QtDebug>
#include <QVariant>
#include <QtDebug>

JobshopModel::JobshopModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

JobshopModel::~JobshopModel()
{
}

bool JobshopModel::setData(const QModelIndex &index, const QVariant &value, int /*role*/)
{
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
        return Jobshop::instance()->m_jobs[section].id();

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
        return section - m_nonOperationColumns /*+ 1*/;
    }
}

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

void JobshopModel::setOperationsCount(int count)
{
    int cc = Jobshop::instance()->operationsCount();
    if(cc == count)
        return;

    if(cc > count)
    {
        beginRemoveColumns(QModelIndex(), columnCount()-1, m_nonOperationColumns + count);
        Jobshop::instance()->setOperationsCount(count);
        endRemoveColumns();
    }
    else if(cc < count)
    {
        beginInsertColumns(QModelIndex(), columnCount(), m_nonOperationColumns + count - 1);
        Jobshop::instance()->setOperationsCount(count);
        endInsertColumns();
    }
}

void JobshopModel::setJobsCount(int count)
{
    int cc = Jobshop::instance()->jobCount();
    if(cc == count)
        return;

    if(cc > count)
    {
        beginRemoveRows(QModelIndex(), count, cc-1);
        Jobshop::instance()->removeJobs(cc-count);
        endRemoveRows();
    }
    else if(cc < count)
    {
        beginInsertRows(QModelIndex(), cc, count-1);
        Jobshop::instance()->addJobs(count-cc);
        endInsertRows();
    }
}

int JobshopModel::columnCount(const QModelIndex & /*parent*/) const
{
    return m_nonOperationColumns + Jobshop::instance()->m_operationsCount;
}

void JobshopModel::loadModel(QDataStream &in)
{
    beginResetModel();
    Jobshop::instance()->load(in);
    endResetModel();
}
