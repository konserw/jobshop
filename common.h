#ifndef common_h
#define common_h

class QString;
class QStringList;

int run(const QString& program, const QStringList& args);
void save(const QString& fileName, const QString& content);

#endif // common_h
