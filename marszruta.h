#ifndef MARSZRUTA_H
#define MARSZRUTA_H

#include <QWidget>

namespace Ui {
    class marszruta;
}

class marszruta : public QWidget {
    Q_OBJECT
public:
    marszruta(QWidget *parent = 0);
    marszruta(qint32 machines, qint32 machine, qint32 time, QWidget *parent = 0);
    marszruta& operator=(const marszruta &in);
    ~marszruta();

    qint32 machine()const;
    qint32 time()const;

    qint32 machines()const;

    QString print()const;

public slots:
    void setMachines(int);

protected:
    void changeEvent(QEvent *e);

    qint32 m;

private:
    Ui::marszruta *ui;
};
QDataStream &operator<<(QDataStream &out, const marszruta &mar);
QDataStream &operator>>(QDataStream &in, marszruta* &mar);
#endif // MARSZRUTA_H
