#include "CutterAltPrc.h"

#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QMap>
#include <QDebug>

#include "data/cutteraltlog.h"
#include "cutterrptparser.h"
#include "utilities/Utility.h"

//CutterAltPrc::CutterAltPrc(QString &p,QString &u)
//{
//    path=p;
//    url=u;
//}
CutterAltPrc::CutterAltPrc(QObject *parent) :
    QThread(parent)
{
    this->isProcessing=false;
    //connect(&http,SIGNAL(httpDone(const bool ,const QString ,const QString )),this,SLOT(postedAlt(bool ,QString ,QString)));
}
void CutterAltPrc::run(){
    logger()->info("CutterAltPrc is starting....");
    this->accessManager = new QNetworkAccessManager();
    int i=0;
    while (!this->global->needTerminate){
        if (this->isProcessing == false){
            checkAltLogs();

        }
        this->sleep(10);
    }
    logger()->info("CutterAltPrc is stopping....");
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
    //QUrl url(global->alrtUrl);
   // http.post(url,map);
    this->post(global->alrtUrl,map);
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
        if (!res){
            logger()->warn(str);
        }
    }else{

        bool res = file.remove();

        int retry=3;
        while (!res && retry >=0){
            this->sleep(1);
            res=file.remove();
            retry--;
        }
        str =QString("Post %1.alm %2,%3 %4").arg(transid).arg("ok").arg("delete").arg(result);
        if (!res){
            logger()->warn(str);
        }
    }
    this->isProcessing=false;
    qDebug()<<str<<endl;
    //emit handled(str);
}

bool CutterAltPrc::post(const QString urlStr,QMap<QString,QString> &map){

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


      this->isProcessing = true;
      this->exec();
    return true;

}

void CutterAltPrc::readyRead(){

    //cout<<"result:"<<text<<endl;
    printf("ReadyRead result:");
}

void CutterAltPrc::finished(){

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

        this->postedAlt(isOk,evtid,result);
        this->exit();

        this->isProcessing=false;
        qDebug()<<"finished:"<<status_code.toInt()<<endl;
}
