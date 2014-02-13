#ifndef RESULTSEMODEL_H
#define RESULTSEMODEL_H

#include <QAbstractTableModel>
#include <Qlist>
#include "Result.h"

/*!
 * \brief The ResultsModel class - representation of chromosome statistics as model for Qt's Model View framework.
 */
class ResultsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ResultsModel(const QList<Result>& results, QObject *parent = 0);
    
signals:
    
public slots:
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

protected:
    const QList<Result>& m_results;
};

#endif // RESULTSEMODEL_H
