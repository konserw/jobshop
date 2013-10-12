#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QGraphicsScene>
#include "wykres.h"

class marszruta;
class Result;
class maszyna;
class zadanie;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(const QString& arg = 0, QWidget *parent = 0);
    ~MainWindow();

    /*zaprzyjaźnienie operatorów serializacji*/
    friend QDataStream &operator<<(QDataStream &out, const MainWindow &win);
    friend QDataStream &operator>>(QDataStream &in, MainWindow &win);

public slots:
    void more(const QString& nazwa, qint32 start, qint32 due, const QList<marszruta *> &marszruty);
    void more();
    void solve();
    void solve(const QString& arg);
    void rout(int);

    void next(qint32, zadanie*);
    void finished(Result*);

    void imp();
    void exp();
    void import(const QString &);

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

/* serializacja - zapis do pliku danych wejściowych */
QDataStream &operator<<(QDataStream &out, const MainWindow &win);
QDataStream &operator>>(QDataStream &in, MainWindow &win);

#endif // MAINWINDOW_H

