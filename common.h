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

#endif // common_h
