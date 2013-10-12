#include "result.h"
#include <cmath>

Result::Result(int j, int cj, int dj, int rj)
{
    _j = j;
    _fj = cj - rj;
    _cj = cj;

    _lj = cj - dj;      //late - spóźnienie
    _ej = 0;            //early - za wcześnie

    if(_lj < 0)
    {
        _ej = std::abs(_lj);
        _lj = 0;
    }
}

bool Result::operator<(const Result other) const
{
    return this->j() < other.j();
}

bool Result::operator>(const Result other) const
{
    return this->j() > other.j();
}

int Result::j() const
{
    return _j;
}

int Result::fj() const
{
    return _fj;
}

int Result::cj() const
{
    return _cj;
}

int Result::lj() const
{
    return _lj;
}

int Result::ej() const
{
    return _ej;
}
