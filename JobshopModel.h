#ifndef JOBSHOPMODEL_H
#define JOBSHOPMODEL_H

#include <QAbstractTableModel>
#include <QList>

//#include "Jobshop.h"
class Jobshop;
class Job;
class QDataStream;


/*!
 * \brief The JobshopModel class - representation of single jobshop scheduling problem as model for Qt's MVC.
 *  Inherits @QAbstractTableModel
 */
class JobshopModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit JobshopModel(QObject* parent = nullptr);
    ~JobshopModel();

public slots:
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int);

    virtual Qt::ItemFlags flags(const QModelIndex &) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

//    virtual bool insertRows(int column, int count, const QModelIndex & parent = QModelIndex());
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
//    virtual bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

//    virtual bool insertColumns(int column, int count, const QModelIndex & parent = QModelIndex());
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
//    virtual bool removeColumns ( int column, int count, const QModelIndex & parent = QModelIndex());

    void loadModel(QDataStream &in);

    static int nonOperationColumns();

    void setOperationsCount(int count);
    void setJobsCount(int count);

protected:
    static const int m_nonOperationColumns = 5;

    friend class Jobshop;
};

#endif // JOBSHOPMODEL_H
