#include "Utility.h"
#include "qjson/parser.h"
#include "qjson/qobjecthelper.h"
#include "qjson/serializer.h"

#include <QDateTime>
#include <QLocale>
Utility::Utility()
{
}

QString Utility::serialize(const QObject  &obj){
    QJson::Serializer serializer;
    QVariantMap variant = QJson::QObjectHelper::qobject2qvariant(&obj);
    QString json = serializer.serialize(variant);
    return json;
}

void Utility::unserialize(const QString &json,QObject &obj, bool &ok){
    QJson::Parser parser;
    QVariant v = parser.parse(json.toLocal8Bit().data(),&ok);
    if (ok){
     QJson::QObjectHelper::qvariant2qobject(v.toMap(), &obj);
    }
 }

 uint Utility::getTs(const QString &timeStr,const QString &dateFormat){
     QLocale lo(QLocale::Chinese);
      QDateTime d = lo.toDateTime(timeStr,dateFormat);

      return d.toTime_t();
 }
