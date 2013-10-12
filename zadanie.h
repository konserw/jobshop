#ifndef ZADANIE_H
#define ZADANIE_H

#include <QObject>
#include <QList>
#include "grafZadanie.h"

class marszruta;
class Result;

class zadanie : public QObject
{
    Q_OBJECT

public:
    zadanie(int number, int start_time, int due_date);
    ~zadanie();

    int time();
    void add_rout(marszruta*);

    int number()const
    {
        return j;
    }

    int due() const
    {
        return dj;
    }

    int arrive() const
    {
        return rj;
    }

    QString print()const;

public slots:
    void update();
    void done();

    QGraphicsItem* gItem();
signals:
    void next(qint32, zadanie*);
    void finished(Result*);
private:
    int j;
    int rj;
    int dj;
    int cur;
    QList<marszruta*> rout;
    bool blocked;

    QList<grafZadanie*> grafiki;
    QColor* col;
};

#endif // ZADANIE_H
