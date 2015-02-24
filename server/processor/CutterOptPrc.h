#ifndef CUTTEROPTPRC_H
#define CUTTEROPTPRC_H

#include <QThread>
#include "Global.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "log4qt/consoleappender.h"
#include "log4qt/logger.h"
#include "log4qt/ttcclayout.h"
#include "data/cutteroptlog.h"
#include "data/cuttermonthlyrpt.h"
#include "data/cutterdailyrpt.h"
class CutterOptPrc : public QThread
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER
public:
    explicit CutterOptPrc(QObject *parent = 0);
    void setGlobal(Global *global);

    void run();
    bool post(const QString urlStr,QMap<QString,QString> &map);

signals:
   // void handled(const QString &msg);
private:
    Global *global;
    QNetworkAccessManager *accessManager;
    QNetworkReply *reply;
    QString evtid;
    //当前是否在上传报警，如果是，则不能处理下一个文件
    bool isProcessing;

    void checkOptLogs();
    void handleOptLog(const QString &filename,CutterOptLog *log,CutterDailyRpt *drpt,CutterMonthlyRpt *mrpt);
    bool uploadOptLog(const QString &filename,CutterOptLog *log,CutterDailyRpt *drpt,CutterMonthlyRpt *mrpt);
    void postedOptLog(bool ok,QString transid,QString result);
public slots:
    //void postedOptLog(bool ok,QString transid,QString result);
    void readyRead();
    void finished();

};

#endif // CUTTEROPTPRC_H
