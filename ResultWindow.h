#ifndef WYKRES_H
#define WYKRES_H

#include "Chromosome.h"

#include <QDialog>

class Result;
class QGraphicsScene;
class QDir;
class Job;

namespace Ui {
    class ResultWindow;
}

class ResultWindow : public QDialog {
    Q_OBJECT
public:
    ResultWindow(QWidget *parent);
    ~ResultWindow();

public slots:
    void setText(const QString& text);
    void finished(Result* x);
    void set(int _maszyn, double _alfa, double _beta);
    void bazinga(const QList<Job *>*);
//    void pdf();
//    void pdf(const QString&fileName);
    void latex();
    void latex(const QString&);
    void evalStats();
    void setupScene();
    void clean();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ResultWindow *ui;

    Chromosome m_chromosome;
    int zadan, maszyn;

    int c;
    double f, l, e, w1, w2, alfa, beta, Tmax, Tsr;

    QGraphicsScene* scene;
};

#endif // WYKRES_H
