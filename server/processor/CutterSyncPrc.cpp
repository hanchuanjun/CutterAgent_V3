#include "CutterSyncPrc.h"
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QMap>
#include <QDebug>
#include <QDateTime>
#include <QLocale>
#include <QTextCodec>
#include <QByteArray>
#include <QSettings>
#include <QNetworkAccessManager>

#include "Utility.h"

CutterSyncPrc::CutterSyncPrc(QObject *parent) :
    QThread(parent)
{
    this->isProcessing=false;

}
void CutterSyncPrc::setGlobal(Global *global){
    this->global =global;
}

void CutterSyncPrc::run(){

    this->accessManager = new QNetworkAccessManager();

    //connect(this,SIGNAL(httpDone(const bool ,const QString,const QString )),this,SLOT(synced(bool ,QString,QString )));


    while (true){
        qDebug()<<"**************  1  *************************sleep 20,this.isProcssing="<<this->isProcessing<<endl;

        if (this->isProcessing == false){
            //同步授权
            this->checkMO();

        }
        qDebug()<<"**************  2  *************************sleep 20,this.isProcssing="<<this->isProcessing<<endl;
        //
        this->sleep(300);
    }
}


void CutterSyncPrc::handleMO(const QString &data){
    QMap<QString,QString> map;
    //map.insert("deviceid","13596034438");
    map.insert("sensorid","33");
    //map.insert("plcid","1");
    map.insert("assetid",this->global->assetId);

    map.insert("eid","1001000000");//global->eid);
    map.insert("data",data);
    QLocale lo(QLocale::Chinese);
    QDateTime d = QDateTime::currentDateTime();
    QString evtid(lo.toString(d,"yyyyMMddhhmmss"));
    map.insert("evtid",evtid);

    post(this->global->licUrl,map);


    map.clear();
    //emit handled(log->toString());
    qDebug()<<"process mo file...."<<evtid<<endl;
}

void CutterSyncPrc::checkMO(){
    QFile src(global->licPath+"hymo.log");
    QString str("");
    if (src.exists())
    {
        if (!src.open(QIODevice::ReadOnly)){
            //error to open the file
            //return null;
        }else{
            QByteArray bytes = src.readAll();
            //QTextCodec *codec = QTextCodec::codecForName("utf-8");
                str= bytes.toHex().data();//codec->toUnicode(bytes);//bytes.toHex();

             qDebug()<<str<<endl;
             src.close();
        }

    }

    this->handleMO(str);

}

void CutterSyncPrc::synced(bool ok,QString transid,QString result){

    qDebug()<<"recevie: ok="<<ok<<";transid="<<transid<<";result="<<result<<endl;
    if (ok){
       QFile src(global->licPath+"hymt.log");
       if (src.exists())
       {
           src.remove();
       }

       qDebug()<<"process mt file..1.."<<global->licPath<<endl;
       if (src.open(QIODevice::WriteOnly)){
            QByteArray data ;
            data = QByteArray::fromHex(result.toUtf8());//.toLocal8Bit());
            //QDataStream out(&src);
            //out<<data;

            src.write(data);

            src.close();

            qDebug()<<"process mt file..2.."<<result<<endl;
       }

       qDebug()<<"process mt file..3.."<<(src.error()== QFile::NoError)<<src.errorString()<<endl;
       //如果文件写入错误，应该记录到日志中
       //-------待实现


    }
    QString str("synchronized...");
    str.append(ok).append("@").append(transid);
    this->isProcessing = false;
   // emit handled(str);
}

bool CutterSyncPrc::post(const QString urlStr,QMap<QString,QString> &map){

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

void CutterSyncPrc::readyRead(){

    //cout<<"result:"<<text<<endl;
    printf("ReadyRead result:");
}

void CutterSyncPrc::finished(){

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

        this->synced(isOk,evtid,result);
        this->exit();

        this->isProcessing=false;
        qDebug()<<"finished:"<<status_code.toInt()<<endl;
}
