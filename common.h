#ifndef common_h
#define common_h

class QString;
class QStringList;

extern int t;
extern bool cli;
extern int fmt;
extern double rot;

int run(const QString& program, const QStringList& args);
void save(const QString& fileName, const QString& content);

template <typename T>
struct PtrLess
{
    bool operator()(const T* a, const T* b) const
    {
        if(a == nullptr) return false;
        if(b == nullptr) return true;
        return *a < *b;
    }
};

#endif // common_h
