#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QGraphicsScene>
#include "JobshopModel.h"

class ResultWindow;
class Operation;
class Result;
class Job;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addJob();
    void solve();

    void exp();
    void import();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    QList<Job*> zadania;
    int skonczone;

    ResultWindow* gant;

    JobshopModel m_model;
};

#endif // MAINWINDOW_H

