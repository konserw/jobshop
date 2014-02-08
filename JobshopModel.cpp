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

    qDebug() << "cc" << cc;
    qDebug() << "count" << count;

/*
    if(cc > count)
        removeColumns(m_nonOperationColumns + cc - count, cc - count);
    else if(cc < count)
        insertColumns(m_nonOperationColumns + cc, count - cc);
*/
    if(cc > count)
    {
        qDebug() << "first" << columnCount()-1;
        qDebug() << "last" <<  m_nonOperationColumns + count;

        beginRemoveColumns(QModelIndex(), columnCount()-1, m_nonOperationColumns + count);
        Jobshop::instance()->setOperationsCount(count);
        endRemoveColumns();
    }
    else if(cc < count)
    {
        qDebug() << "first" << columnCount();
        qDebug() << "last" <<  m_nonOperationColumns + count - 1;

        beginInsertColumns(QModelIndex(), columnCount(), m_nonOperationColumns + count - 1);//columnCount() + count - cc);
        Jobshop::instance()->setOperationsCount(count);
        endInsertColumns();
    }
}

void JobshopModel::setJobsCount(int count)
{
    int cc = Jobshop::instance()->jobCount();
    if(cc == count)
        return;

    qDebug() << "cc" << cc;
    qDebug() << "count" << count;

    /*
    if(cc > count)
        removeRows(cc-count, count);
    else if(cc < count)
        insertRows(cc, count-cc);
        */

    if(cc > count)
    {
        qDebug() << "first" << count;
        qDebug() << "last" <<  cc-1;

        beginRemoveRows(QModelIndex(), count, cc-1);
        Jobshop::instance()->removeJobs(cc-count);
        endRemoveRows();
    }
    else if(cc < count)
    {
        qDebug() << "first" << cc;
        qDebug() << "last" << count-1;

        beginInsertRows(QModelIndex(), cc, count-1);
        Jobshop::instance()->addJobs(count-cc);
        endInsertRows();
    }
}

int JobshopModel::columnCount(const QModelIndex & /*parent*/) const
{
    return m_nonOperationColumns + Jobshop::instance()->m_operationsCount;
}
/*
bool JobshopModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(count < 1)
        return false;

    beginInsertRows(parent, row, row+count-1);
    Jobshop::instance()->addJobs(count);
    endInsertRows();
    return true;
}

bool JobshopModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(count < 1)
        return false;

    beginRemoveRows(parent, row, row+count-1);
    Jobshop::instance()->removeJobs(count);
    endRemoveRows();
    return true;
}

bool JobshopModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    if(count < 1)
        return false;

    qDebug() << "column" << column;
    qDebug() << "count" << count;

    qDebug() << "first" << column;
    qDebug() << "last" << column+count-1;

    beginInsertColumns(parent, column, column+count-1);
    Jobshop::instance()->setOperationsCount(column+count-m_nonOperationColumns);
    endInsertColumns();
    return true;
}

bool JobshopModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    if(count < 1)
        return false;

    qDebug() << "column" << column;
    qDebug() << "count" << count;

    qDebug() << "first" << column;
    qDebug() << "last" << column+count-1;

    beginRemoveColumns(parent, column, column+count-1);
    Jobshop::instance()->setOperationsCount(column-m_nonOperationColumns);
    endRemoveColumns();
    return true;
}
*/
void JobshopModel::loadModel(QDataStream &in)
{
    beginResetModel();
    Jobshop::instance()->load(in);
    endResetModel();
}
