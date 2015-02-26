#include "CutterOptPrc.h"
#include "cutterrptparser.h"

#include <QFile>
#include <QDir>
#include <QDebug>

#include "utilities/Utility.h"

CutterOptPrc::CutterOptPrc(QObject *parent) :
    QThread(parent)
{
    this->isProcessing=false;
    //connect(&http,SIGNAL(httpDone(const bool ,const QString ,const QString)),this,SLOT(postedOptLog(bool ,QString , QString)));
}
void CutterOptPrc::run(){
    logger()->info("CutteOptPrc is starting....");
    this->accessManager = new QNetworkAccessManager();

    int i=0;
    while (!this->global->needTerminate){
        if (this->isProcessing == false){
            checkOptLogs();
            logger()->debug(!this->isProcessing?"CutterOptPrc is processing alarm files ...":"CutterOptPrc is not processing alarm files ...");

        }
        this->sleep(10);
    }

    logger()->info("CutterOptPrc is stopping....");
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
                //由于http异步，因此，一次只处理一个，等待http异步返回
                this->isProcessing=true;
                //如果更名成功，则上传记录，并等待
                this->uploadOptLog(evtid,log,drpt,mrpt);
                delete log;
                delete drpt;
                delete mrpt;
                logger()->debug(QString("Handle opt file[").append(file).append("->").append(dest)
                                .append(") and upload it!"));
                break;
            }else{
                //如果更名不成,则放弃,然后执行下一个文件,当前文件下次循环再处理
                logger()->warn(QString("Failed to rename ").append(file).append(" to ").append(dest));

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

    this->post(global->alrtUrl,map);

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
        if (res){
            str =QString("Post %1.evt %2,%3 %4").arg(transid).arg("nok").arg("rename").arg(result);
            logger()->debug(str);
        }else
            str =QString("Post %1.evt %2,failed to %3 %4").arg(transid).arg("nok").arg("rename").arg(result);
        if (!res){
            logger()->warn(str);
        }
    }else{

        bool res = file.remove();
        int retry=3;
        while (!res && retry >=0){
            this->sleep(10);
            res=file.remove();
            retry--;
        }
        if(res){
            str =QString("Post %1.evt %2,Successed to %3 %4").arg(transid).arg("ok").arg("delete").arg(result);
            logger()->debug(str);
        }else{
            str =QString("Post %1.evt %2, failed to %3 %4!").arg(transid).arg("ok").arg("delete").arg(result);
            logger()->warn(str);
        }
    }
    this->isProcessing=false;
    //emit handled(str);
}

bool CutterOptPrc::post(const QString urlStr,QMap<QString,QString> &map){

    //this->isFilished = false;
    QString params = "";
    QString key,value;
    QList<QString> list = map.keys();
    QListIterator<QString> i(list);

    while (i.hasNext()){
        key=i.next();
        value=map.value(key);
        params.append(key).append("=").append(value);
        if (key.toLower() == "evtid"){
            evtid= value;
        }
        if (i.hasNext()){
            params.append("&");
        }
    }

    params = params.replace(" ","%20");


     QUrl url(urlStr+"?"+params);
       // QUrl url("http://www.google.com/d.html?"+params);

      reply=accessManager->get(QNetworkRequest(url));
      connect(reply, SIGNAL(finished()), this, SLOT(finished()));
      connect(reply, SIGNAL(readyRead()), this, SLOT(readyRead()));

      this->exec();
    return true;

}

void CutterOptPrc::readyRead(){

    //cout<<"result:"<<text<<endl;
    printf("ReadyRead result:");
}

void CutterOptPrc::finished(){

    //cout<<"result:"<<text<<endl;;
    //获取响应的信息，状态码为200表示正常
      QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

      QString result;
      bool isOk=true;
      //无错误返回
      if(reply->error() == QNetworkReply::NoError)
      {
          QByteArray bytes = reply->readAll();
          result.append(bytes);  //转化为字符串
          qDebug()<<result<<endl;
        }
        else
        {
          //处理错误
          isOk=false;
          result="error";
        }

        reply->deleteLater();//要删除reply，但是不能在repyfinished里直接delete，要调用deletelater;

       // if (this->isFilished){
            //emit httpDone(!isOk,evtid,result);
       // }

        this->postedOptLog(isOk,evtid,result);
        this->exit();

        this->isProcessing=false;
        qDebug()<<"finished:"<<status_code.toInt()<<endl;
}
