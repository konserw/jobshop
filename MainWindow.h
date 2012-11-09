#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QGraphicsScene>
#include "wykres.h"

class marszruta;
class stat;
class maszyna;
class zadanie;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    friend QDataStream &operator<<(QDataStream &out, const MainWindow &win);
    friend QDataStream &operator>>(QDataStream &in, MainWindow &win);

public slots:
    void more(qint32 start, qint32 due, QList<marszruta *> &marszruty);
    void more();
    void solve();
    void rout(int);

    void next(qint32, zadanie*);
    void finished(stat*);

    void imp();
    void exp();

signals:
    void tick();
    void tick2();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    QList<maszyna*> maszyny;
    QList<zadanie*> zadania;
    int skonczone;

    QGraphicsScene* scene;
    wykres* gant;

};

QDataStream &operator<<(QDataStream &out, const MainWindow &win);
QDataStream &operator>>(QDataStream &in, MainWindow &win);

#endif // MAINWINDOW_H

