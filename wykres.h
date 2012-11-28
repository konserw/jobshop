#ifndef WYKRES_H
#define WYKRES_H

#include <QDialog>

struct stat;
class QGraphicsScene;

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
    void finished(stat* x);
    void set(int _maszyn, double _alfa, double _beta);
    void bazinga();
    void bazinga(const QString& filename);
    void pdf();
    void pdf(const QString& filename);
    void evalStats();
    void setupScene();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wykres *ui;

    QList<stat*> stats;
    int zadan, maszyn;

    int c;
    double f, l, e, w1, w2, alfa, beta;

    QGraphicsScene* scene;
};

#endif // WYKRES_H
