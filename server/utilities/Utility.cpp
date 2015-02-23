#include "Utility.h"


#include <QDateTime>
#include <QLocale>
Utility::Utility()
{
}


 uint Utility::getTs(const QString &timeStr,const QString &dateFormat){
     QLocale lo(QLocale::Chinese);
      QDateTime d = lo.toDateTime(timeStr,dateFormat);

      return d.toTime_t();
 }
