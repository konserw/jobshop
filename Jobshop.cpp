#include "Jobshop.h"
#include "JobshopModel.h"
#include "Operation.h"

#include <QtDebug>
#include <cmath>

Jobshop* Jobshop::m_instance = nullptr;

Jobshop::Jobshop()
    : m_operationsCount(0),
      m_machinesCount(1),
      m_model(nullptr)
{
}

Jobshop::~Jobshop()
{ qDebug() << "destroy singleton"; }

Jobshop *Jobshop::instance()
{
    if(m_instance == nullptr)
        m_instance = new Jobshop;
    return m_instance;
}

JobshopModel *Jobshop::model()
{
    if(m_model == nullptr)
        m_model = new JobshopModel(this);
    return m_model;
}

void Jobshop::solve()
{
    /*
    skonczone = 0;
    t = 0;
    maszyna* m;
    zadanie* z;
    qint32 i;
    qint32 zadan, maszyn;

    ui->centralWidget->setEnabled(false);

    for(i=0; i<ui->machines->value(); i++)
    {
        m = new maszyna(i+1, scene);
        connect(this, SIGNAL(tick()), m, SLOT(update()));
        connect(this, SIGNAL(tick2()), m, SLOT(up2()));
        maszyny.append(m);
    }
    maszyn = i;

    for(i=0; i<ui->tableWidget->rowCount(); i++)
    {
        z = new zadanie(i+1, ui->tableWidget->item(i, 1)->text().toInt(), ui->tableWidget->item(i, 2)->text().toInt());
        for(qint32 j=3; j<ui->tableWidget->columnCount(); j++)
            z->add_rout(qobject_cast<marszruta*>(ui->tableWidget->cellWidget(i, j)));

        connect(z, SIGNAL(next(qint32,zadanie*)), this, SLOT(next(qint32,zadanie*)));
        connect(z, SIGNAL(finished(Result*)), this, SLOT(finished(Result*)));
        connect(z, SIGNAL(finished(Result*)), gant, SLOT(finished(Result*)));
        connect(this, SIGNAL(tick()), z, SLOT(update()));

        zadania.append(z);
    }
    zadan = i;

    do
    {
        emit tick();
        emit tick2();
        t++;
    }while(zadan > skonczone);

    gant->set(maszyn, ui->alfa->value(), ui->beta->value());
    if(cli)
        gant->bazinga(arg, &zadania);
    else
        gant->bazinga(&zadania);

    foreach(z, zadania)
        delete z;
    foreach(m, maszyny)
        delete m;

    zadania.clear();
    maszyny.clear();

    scene->clear();

    ui->centralWidget->setEnabled(true);
    */
}

void Jobshop::addJob()
{
    int row = m_jobs.count();
    m_jobs.append(Job(m_operationsCount));
    m_model->insertRow(row);
}

int Jobshop::operationsCount() const
{
    return m_operationsCount;
}

void Jobshop::setOperationsCount(int operationsCount)
{
    int diff = operationsCount - m_operationsCount; //number of columns to be added
    if(!diff) //no change
        return;

    for(Job& job : m_jobs)
        job.setOperationsCount(operationsCount);

    if(diff > 0)//adding rows
        m_model->insertColumns(m_operationsCount, diff);
    else
        m_model->removeColumns(operationsCount, std::abs(diff));

    m_operationsCount = operationsCount;
}

int Jobshop::machinesCount() const
{
    return m_machinesCount;
}

void Jobshop::setMachinesCount(int machinesCount)
{
    m_machinesCount = machinesCount;
}

QDataStream &operator <<(QDataStream &out, const Jobshop &jobshop)
{
    qint64 operations = qint64(jobshop.m_operationsCount);
    qint64 machines = qint64(jobshop.m_machinesCount);
    qint64 jobs = qint64(jobshop.m_jobs.count());

    out << operations
        << machines
        << jobs;

    for(qint32 i=0; i<jobs; ++i)
    {
        out << jobshop.m_jobs[i];
    }

    return out;
}

QDataStream &operator >>(QDataStream &in, Jobshop &jobshop)
{
    jobshop.m_model->removeRows(0, jobshop.m_jobs.count());
   // jobshop.m_model->beginResetModel();
    jobshop.m_jobs.clear();

    qint64 operations;
    qint64 machines;
    qint64 jobs;

    in  >> operations
        >> machines
        >> jobs;

    jobshop.m_operationsCount = operations;
    jobshop.m_machinesCount = machines;

    for(qint64 i=0; i<jobs; ++i)
    {
        Job job;
        in >> job;
        jobshop.m_jobs.append(job);
    }

    return in;
    jobshop.m_model->insertRows(0, jobshop.m_jobs.count());
//    jobshop.m_model->modelReset();
}

