#ifndef CUTTERSYNCPRC_H
#define CUTTERSYNCPRC_H

#include <QThread>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "log4qt/consoleappender.h"
#include "log4qt/logger.h"
#include "log4qt/ttcclayout.h"
#include "Global.h"

class CutterSyncPrc : public QThread
{
    Q_OBJECT
public:
    explicit CutterSyncPrc(QObject *parent = 0);
    void setGlobal(Global *global);

    void run();
    bool post(const QString urlStr,QMap<QString,QString> &map);

signals:
    //void handled(const QString &msg);
    //void httpDone(const bool &error,const QString &transid,const QString &result);
private:
    Global *global;
    QNetworkAccessManager *accessManager;
    QNetworkReply *reply;
    QString evtid;
    //bool isFilished;
    //当前是否在上传报警，如果是，则不能处理下一个文件
    bool isProcessing;

    void checkMO();
    void handleMO(const QString &data);

    void synced(bool ok,QString transid,QString result);
public slots:
    //void synced(bool ok,QString transid,QString result);
    void readyRead();
    void finished();




};



#endif // CUTTERSYNCPRC_H
