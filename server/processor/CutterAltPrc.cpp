#include "CutterAltPrc.h"

#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QMap>
#include <QDebug>

#include "cutteraltlog.h"
#include "cutterrptparser.h"
#include "Utility.h"

//CutterAltPrc::CutterAltPrc(QString &p,QString &u)
//{
//    path=p;
//    url=u;
//}
CutterAltPrc::CutterAltPrc()
{
    this->isProcessing=false;
    connect(&http,SIGNAL(httpDone(const bool ,const QString ,const QString )),this,SLOT(postedAlt(bool ,QString ,QString)));
}
void CutterAltPrc::run(){
    int i=0;
    while (true){
        if (this->isProcessing == false){
            checkAltLogs();

        }
        this->sleep(10);
    }
}

void CutterAltPrc::checkAltLogs(){
    QDir dir(global->alrtLogPath);
    QStringList filters;
    filters += "*.alm";

    foreach(QString file,dir.entryList(filters,QDir::Files)){

        qDebug()<<"filename:"<<file<<endl;
        CutterAltLog* log = handleAlrtLog(file);
        if (log->getS001() == ""){
            QFile dest(global->alrtLogPath+file);
            dest.remove();
        }else{

            QFile src(global->alrtLogPath+file);
            QString evtid=file.mid(0,file.length()-4);

            QString dest = global->alrtLogPath+evtid+".his";
            bool result = src.rename(dest);
            qDebug()<<file<<" to "<<dest<<"  " <<result<<endl;
            if (result){
                this->uploadEvt(evtid,log);
                delete log;
                //由于http异步，因此，一次只处理一个，等待http异步返回
                this->isProcessing=true;
                break;
            }

        }
        //Log4Qt::Logger::logger(QLatin1String("file "))->info("file!");
   }
}
void CutterAltPrc::setGlobal(Global *global){
    this->global =global;
}

CutterAltLog* CutterAltPrc::handleAlrtLog(const QString &filename){

    CutterRptParser parser;
    QString filePath = global->alrtLogPath+filename;
    return parser.parseAlrtLog(filePath);


}

bool CutterAltPrc::uploadEvt(const QString &filename,CutterAltLog *log)
{
    QMap<QString,QString> map;
    //map.insert("deviceid","13676027529");
    map.insert("sensorid","33");
    //map.insert("plcid","1");
    map.insert("assetid",global->assetId);
    map.insert("evtid",filename);
    //QString str=QString("%1").arg(log->getTs());
    //map.insert("ts",str);
    QString ts = QString::number(Utility::getTs(log->getS003(),tr("yyyy/MM/dd hh:mm:ss")));

    map.insert("ts",ts);
    map.insert("eid","1001000000");//global->eid);
    map.insert("evt_type","99");
    map.insert("content",log->toString());
    QUrl url(global->alrtUrl);
    http.post(url,map);
    map.clear();
    //emit handled(log->toString());
    qDebug()<<log->toString()<<endl;
    return true;
}

void CutterAltPrc::postedAlt(bool ok,QString transid,QString result){
    //QString src=QString(transid+".alm");

    bool isOk=ok;
    if (result.toLower() == "ok"){
        isOk &= true;
    }

    QString dest=QString(global->alrtLogPath+transid+".his");
    QFile file(dest);
    QString str;

    if (!isOk){

        bool res = file.rename(global->alrtLogPath+transid+".alm");

        int retry=3;
        while (!res && retry >=0){
            this->sleep(1);
            res=file.rename(global->alrtLogPath+transid+".alm");
            retry--;
        }
        str =QString("Post %1.alm %2,%3 %4").arg(transid).arg("nok").arg("rename").arg(result);

    }else{

        bool res = file.remove();

        int retry=3;
        while (!res && retry >=0){
            this->sleep(1);
            res=file.remove();
            retry--;
        }
        str =QString("Post %1.alm %2,%3 %4").arg(transid).arg("ok").arg("delete").arg(result);
    }
    this->isProcessing=false;
    qDebug()<<str<<endl;
    emit handled(str);
}
