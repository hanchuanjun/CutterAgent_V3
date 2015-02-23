#ifndef CUTTERALTPRC_H
#define CUTTERALTPRC_H

#include <QThread>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "log4qt/consoleappender.h"
#include "log4qt/logger.h"
#include "log4qt/ttcclayout.h"
#include "data/cutteraltlog.h"
#include "Global.h"
class CutterAltPrc : public QThread
{
    Q_OBJECT
public:
    explicit CutterAltPrc(QObject *parent = 0);//QString &p,QString &u);
    void setGlobal(Global *global);

    void run();
    bool post(const QString urlStr,QMap<QString,QString> &map);

signals:
    //void handled(const QString &msg);
private:
    Global *global;
    QNetworkAccessManager *accessManager;
    QNetworkReply *reply;
    QString evtid;
    //��ǰ�Ƿ����ϴ�����������ǣ����ܴ�����һ���ļ�
    bool isProcessing;

    void checkAltLogs();
    CutterAltLog* handleAlrtLog(const QString &filename);
    bool uploadEvt(const QString &filename,CutterAltLog *log);
     void postedAlt(bool ok,QString transid,QString result);
public slots:
    //void postedAlt(bool ok,QString transid,QString result);
     void readyRead();
     void finished();
};

#endif // CUTTERALTPRC_H
