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
    wykres(QWidget *parent, QGraphicsScene* s);
    ~wykres();

public slots:
    void setText(QString& s);
    void finished(stat* x);
    void set(int maszyn);
    void up(int);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wykres *ui;

    QList<stat*> s;
    int zadan;

    int c;
    double f, l, e, sum;
};

#endif // WYKRES_H
