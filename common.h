#ifndef common_h
#define common_h

#include <QDebug>

extern int t;
extern bool cli;

#define dx 20
#define dy 18

#define DEBUG qDebug() << __FILE__ << " (" << __LINE__ << "): "

class stat
{
public:
    stat(int j, int cj, int dj, int rj)
    {
        _j = j;
        _fj = cj - rj;
        _cj = cj;

        _lj = cj - dj;      //late - spóźnienie
        _ej = 0;            //early - za wcześnie

        if(_lj < 0)
        {
            _ej = abs(_lj);
            _lj = 0;
        }
    }

    int j()
    {
        return _j;
    }
    int fj()
    {
        return _fj;
    }
    int cj()
    {
        return _cj;
    }
    int lj()
    {
        return _lj;
    }
    int ej()
    {
        return _ej;
    }

private:
    int _j, _fj, _cj, _lj, _ej;

};

#endif // common_h
