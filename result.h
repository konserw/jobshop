#ifndef RESULT_H
#define RESULT_H

class Result
{
public:
    Result(int j, int cj, int dj, int rj);

    bool operator<(const Result other) const;
    bool operator>(const Result other) const;

    int j() const;
    int fj() const;
    int cj() const;
    int lj() const;
    int ej() const;

private:
    int _j, _fj, _cj, _lj, _ej;
};

bool comparecompletionTime(const Result& a, const Result& b);

#endif // RESULT_H
