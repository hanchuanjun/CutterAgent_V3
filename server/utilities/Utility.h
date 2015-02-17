#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include <QObject>
class Utility
{
public:
    Utility();
    //object -> json string
    static QString serialize(const QObject  &obj);
    //json -> object
    static void unserialize(const QString &json,QObject &obj, bool &ok);
    //parse datetime
    static uint getTs(const QString &timeStr,const QString &dateFormat);
};

#endif // UTILITY_H
