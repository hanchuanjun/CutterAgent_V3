#ifndef CUTTERRPTPARSER_H
#define CUTTERRPTPARSER_H

#include <QString>
#include "cuttermonthlyrpt.h"
#include "cutterdailyrpt.h"
#include "CutterAltLog.h"
#include "cutteroptlog.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>

class CutterRptParser
{
public:
    int mOpts;
    int dOpts;
    int rOpts;
    int aOpts;


    CutterRptParser();

    void parseMonthlyReport(QString &filename,CutterMonthlyRpt *mRpt);
    void parseDailyReport(QString &filename,CutterDailyRpt *dRpt);
    void parseOptLog(QString &filename,CutterOptLog *optLog);
    CutterAltLog* parseAlrtLog(QString &filename);

 private:
    void parse1stConf(const QString &str);
    void parseDailyReportItem(const QString &args,CutterDailyRpt &rpt);
    void parseMonthlyReportItem(const QString &args,CutterMonthlyRpt &rpt);
    void parseOptLogItem(const QString &args,CutterOptLog &rpt);
    void parseAlrtItem(const QString &args,CutterAltLog &rpt);
    QString getValue(const QString &arg);

};

#endif // CUTTERRPTPARSER_H
