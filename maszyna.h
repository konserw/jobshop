#ifndef MASZYNA_H
#define MASZYNA_H

#include <QObject>
#include <QList>

class QGraphicsScene;
class zadanie;

class maszyna : public QObject
{
     Q_OBJECT

public:
    maszyna(int id, QGraphicsScene* scene);
    ~maszyna();

    static int method;
    static const int X0 = 35;

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
    QFont* font;
    QPen* pen;
    QPen* penKonflikt;
};

#endif // MASZYNA_H
