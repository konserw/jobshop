#define MASZYNA_H
#ifndef MASZYNA_H
#define MASZYNA_H

#include <QObject>
#include <QList>

class Job;

QT_BEGIN_NAMESPACE
    class QGraphicsScene;
    class QFont;
    class QPen;
QT_END_NAMESPACE

class maszyna : public QObject
{
     Q_OBJECT

public:
    maszyna(int id, QGraphicsScene* scene);
    ~maszyna();

    static const int X0 = 35;

public slots:
    void update();
    void add(Job*);
    void up2();

private:
    void start(Job*);

    int stop;
    Job* cur;
    QList<Job*> kolejka;
    int _id;

    QGraphicsScene* scene;
    qreal x, y;
    QFont* font;
    QPen* pen;
    QPen* penKonflikt;
};

#endif // MASZYNA_H
