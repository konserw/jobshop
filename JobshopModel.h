#ifndef JOBSHOPMODEL_H
#define JOBSHOPMODEL_H

#include <QAbstractTableModel>
#include <QList>

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

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex & = QModelIndex()) const;


    void addJob();
    void addJob(Job *job);

    qint32 machinesCount() const;
    void setMachinesCount(const qint32 &machinesCount);

    static int nonOperationColumns();

    qint32 operationsCount() const;
    void setOperationsCount(const qint32 &operationsCount);

public slots:
    void clear();

protected:
    QList<Job*> m_jobs; //not Steve

    qint32 m_machinesCount;
    qint32 m_operationsCount;
    static const int m_nonOperationColumns = 5;

    friend QDataStream &operator<<(QDataStream &out, const JobshopModel & model);
    friend QDataStream &operator>>(QDataStream &in, JobshopModel & model);
};

QDataStream &operator<<(QDataStream &out, const JobshopModel & model);
QDataStream &operator>>(QDataStream &in, JobshopModel & model);

extern JobshopModel* jobModel;
#endif // JOBSHOPMODEL_H
