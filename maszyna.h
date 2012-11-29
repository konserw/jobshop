#ifndef MASZYNA_H
#define MASZYNA_H

#include <QObject>
#include <QList>
#include <QtGui>

class zadanie;

class maszyna : public QObject
{
     Q_OBJECT

public:
    maszyna(int id, QGraphicsScene* scene);
    ~maszyna();

    static int method;

public slots:
    void update();
    void add(zadanie*);
    void up2();


private:
    void start(zadanie*);

    int stop;
    zadanie* cur;
    QList<zadanie*> kolejka;
    int _id;

    QGraphicsScene* scene;
    qreal x, y;
    QGraphicsLineItem* line;
    QFont* font;
    QPen* pen;
};

#endif // MASZYNA_H
