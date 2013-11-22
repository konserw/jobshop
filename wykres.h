#ifndef WYKRES_H
#define WYKRES_H

#include <QDialog>

class Result;
class QGraphicsScene;
class QDir;
class Job;

namespace Ui {
    class wykres;
}

class wykres : public QDialog {
    Q_OBJECT
public:
    wykres(QWidget *parent, QGraphicsScene* _scene);
    ~wykres();

public slots:
    void setText(const QString& text);
    void finished(Result* x);
    void set(int _maszyn, double _alfa, double _beta);
    void bazinga(const QList<Job *>*);
    void bazinga(const QString&, const QList<Job *>*);
    void pdf();
    void pdf(const QString&fileName);
    void latex();
    void latex(const QString&);
    void evalStats();
    void setupScene();
    void clean();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wykres *ui;

    QList<Result*> stats;
    int zadan, maszyn;

    int c;
    double f, l, e, w1, w2, alfa, beta, Tmax, Tsr;

    const QList<Job*> *zadania;
    QGraphicsScene* scene;

    //for result sorting:
    template <typename T>
    class PtrLess
    {
    public:
        bool operator()(const T* a, const T* b) const
        {
            if(a == nullptr) return false;
            if(b == nullptr) return true;
            return *a < *b;
        }
    };
};

#endif // WYKRES_H
