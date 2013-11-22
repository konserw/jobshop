#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QGraphicsScene>
#include "wykres.h"

class Operation;
class Result;
class maszyna;
class Job;

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
    void more(const QString& nazwa, qint32 start, qint32 due, const QList<Operation *> &marszruty);
    void more();
    void solve(const QString& arg = QString());
    void rout(int);

    void next(qint32, Job*);
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
    QList<Job*> zadania;
    int skonczone;

    QGraphicsScene* scene;
    wykres* gant;
};

/* serializacja - zapis do pliku danych wejściowych */
QDataStream &operator<<(QDataStream &out, const MainWindow &win);
QDataStream &operator>>(QDataStream &in, MainWindow &win);

#endif // MAINWINDOW_H

