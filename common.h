#ifndef common_h
#define common_h

#include <QDebug>

extern int t;
extern bool cli;
extern int fmt;
extern double rot;

const int dx = 9;
const int dy = 20;
const int X0 = 35;

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

#endif // common_h
