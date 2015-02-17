#ifndef CUTTERALTPRC_H
#define CUTTERALTPRC_H

#include <QThread>
#include <QString>
#include "cutteraltlog.h"
#include "Global.h"
#include "utiities/JSonRpcSvc.h"
class CutterAltPrc : public QThread
{
    Q_OBJECT
public:
    explicit CutterAltPrc();//QString &p,QString &u);
    void setGlobal(Global *global);

    void run();

signals:
    void handled(const QString &msg);
private:
    Global *global;
    JSonRpcSvc  http;
    //当前是否在上传报警，如果是，则不能处理下一个文件
    bool isProcessing;

    void checkAltLogs();
    CutterAltLog* handleAlrtLog(const QString &filename);
    bool uploadEvt(const QString &filename,CutterAltLog *log);

public slots:
    void postedAlt(bool ok,QString transid,QString result);
};

#endif // CUTTERALTPRC_H
