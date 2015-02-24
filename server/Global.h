#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
class Global
{
public:
    const static int EVENT_UNKONW =1;
    const static int EVENT_ALERT = 2;
    const static int EVENT_REPORT = 3;
    bool needTerminate = false;
    Global();
    void init();

    QString eid;
    //资产编号
    QString assetId;
    //和鹰操作日志路径
    QString optLogPath;
    //日报、月报文件路径
    QString rptPath;
    //授权文件路径
    QString licPath;
    //告警文件路径
    QString alrtLogPath;
    //操作日志上传url
    QString optLogUrl;
    //日/月报上传url
    QString rptUrl;
    //告警上传url
    QString alrtUrl;
    //授权同步url
    QString licUrl;
    //实时数据上传url
    QString instDataPath;

    QString windir;
};

#endif // GLOBAL_H
