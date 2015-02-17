#include "CutterOptPrc.h"
#include "cutterrptparser.h"

#include <QFile>
#include <QDir>
#include <QDebug>

#include "utility.h"

CutterOptPrc::CutterOptPrc()
{
    this->isProcessing=false;
    connect(&http,SIGNAL(httpDone(const bool ,const QString ,const QString)),this,SLOT(postedOptLog(bool ,QString , QString)));
}
void CutterOptPrc::run(){

    int i=0;
    while (true){
        if (this->isProcessing == false){
            checkOptLogs();

        }
        this->sleep(10);
    }
}

void CutterOptPrc::checkOptLogs(){
    QDir dir(global->optLogPath);
    QStringList filters;
    filters += "*.evt";

    foreach(QString file,dir.entryList(filters,QDir::Files)){

        QTextStream out(stdout);
        out<<"filename:"<<file<<endl;
        CutterOptLog* log= new CutterOptLog();
        CutterDailyRpt *drpt=new CutterDailyRpt();
        CutterMonthlyRpt *mrpt = new CutterMonthlyRpt();
        handleOptLog(file,log,drpt,mrpt);
        if (log->getS001() == ""){
            QFile dest(global->optLogPath+file);
            dest.remove();
        }else{

            QFile src(global->optLogPath+file);
            QString evtid=file.mid(0,file.length()-4);

            QString dest = global->optLogPath+evtid+".his";
            bool result = src.rename(dest);
            qDebug()<<"rename "<<file<<" to "<<dest<<(result?"true":"false")<<endl;
            if(result){
                //如果更名成功，则上传记录，并等待
                this->uploadOptLog(evtid,log,drpt,mrpt);
                delete log;
                delete drpt;
                delete mrpt;
                //由于http异步，因此，一次只处理一个，等待http异步返回
                this->isProcessing=true;
                break;
            }else{
                //如果更名不成,则放弃,然后执行下一个文件,当前文件下次循环再处理

            }

        }
        //Log4Qt::Logger::logger(QLatin1String("file "))->info("file!");
    }
}
void CutterOptPrc::setGlobal(Global *global){
    this->global =global;
}

void CutterOptPrc::handleOptLog(const QString &filename,CutterOptLog *log,CutterDailyRpt *drpt,CutterMonthlyRpt *mrpt){

    CutterRptParser parser;
    QString filePath = global->optLogPath+filename;
    parser.parseOptLog(filePath,log);
    if (!log->getS005().isEmpty()){
        QString dateField = log->getS005().replace("/","");
        qDebug()<<"src:"<<log->getS005()<<" ---> "<<dateField<<endl;
        QString rptFilePath = global->rptPath+"\\Nippou\\"+dateField+".nip";
        QFile file(rptFilePath);
        if (!file.exists()){
            rptFilePath = global->rptPath+"NIPPOU.NIP";
            //file(rptFilePath);
        }

        parser.parseDailyReport(rptFilePath,drpt);
        parser.parseMonthlyReport(rptFilePath,mrpt);

    }

}

bool CutterOptPrc::uploadOptLog(const QString &filename,CutterOptLog *log,CutterDailyRpt *drpt,CutterMonthlyRpt *mrpt)
{
    QMap<QString,QString> map;
    map.insert("eid","1001000000");//global->eid);
    //map.insert("deviceid","13596034438");
    map.insert("sensorid","33");
    //map.insert("plcid","1");
    map.insert("assetid",global->assetId);
    map.insert("evtid",filename);
    //QString str=QString("%1").arg(log->getTs());
    //map.insert("ts",str);
    QString time=QString("%1 %2").arg(log->getS005()).arg(log->getS006());
    QString ts = QString::number(Utility::getTs(time,tr("yyyy/MM/dd hh:mm:ss")));

    map.insert("ts",ts);
    map.insert("evt_type","100");
   // QString content;
   //content.append("{\"")
    map.insert("content",log->toString());
    map.insert("content1",drpt->toString());
    map.insert("content2",mrpt->toString());
    QUrl url(global->alrtUrl);
    http.post(url,map);

    //emit handled(log->toString());
    return true;
}

void CutterOptPrc::postedOptLog(bool ok,QString transid,QString result){
    //QString src=QString(transid+".alv");
    bool isOk=ok;
    if (result.toLower() == "ok"){
        isOk &= true;
    }

    QString dest=QString(global->optLogPath+transid+".his");
    QFile file(dest);
    QString str;

    if (!isOk){

        bool res = file.rename(global->optLogPath+transid+".evt");
        int retry=3;
        while (!res && retry >=0){
            this->sleep(10);
            res=file.rename(global->optLogPath+transid+".evt");
            retry--;
        }
        if (res)
            str =QString("Post %1.evt %2,%3 %4").arg(transid).arg("nok").arg("rename").arg(result);
        else

            str =QString("Post %1.evt %2,failed to %3 %4").arg(transid).arg("nok").arg("rename").arg(result);
    }else{

        bool res = file.remove();
        int retry=3;
        while (!res && retry >=0){
            this->sleep(10);
            res=file.remove();
            retry--;
        }
        if(res)
            str =QString("Post %1.evt %2,Successed to %3 %4").arg(transid).arg("ok").arg("delete").arg(result);
        else
            str =QString("Post %1.evt %2, failed to %3 %4!").arg(transid).arg("ok").arg("delete").arg(result);
    }
    this->isProcessing=false;
    emit handled(str);
}
