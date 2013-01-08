#ifndef common_h
#define common_h

#include <QDebug>

extern int t;
extern bool cli;
extern int fmt;

#define dx 9
#define dy 20
#define X0 35

#define DEBUG qDebug() << __FILE__ << " (" << __LINE__ << "): "

int run(const QString& program, const QStringList& args);
void save(const QString& fileName, const QString& content);

template <typename T>
struct PtrLess
{
    bool operator()(const T* a, const T* b) const
    {
        if(a == NULL) return false;
        if(b == NULL) return true;
        return *a < *b;
    }
};


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

    bool operator<(const stat other) const
    {
        return this->j() < other.j();
    }

    bool operator>(const stat other) const
    {
        return this->j() > other.j();
    }

    int j() const
    {
        return _j;
    }
    int fj() const
    {
        return _fj;
    }
    int cj() const
    {
        return _cj;
    }
    int lj() const
    {
        return _lj;
    }
    int ej() const
    {
        return _ej;
    }

private:
    int _j, _fj, _cj, _lj, _ej;

};

#endif // common_h
