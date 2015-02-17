#include "cutteraltlog.h"
CutterAltLog::CutterAltLog(QObject *parent) :
    QObject(parent)
{
}
    QString CutterAltLog::toString(){
        QJsonObject json ;
        json.insert("s001",s001);
        json.insert("s002",s002);
        json.insert("s003",s003);

        QJsonDocument document;
        document.setObject(json);
        QByteArray barray = document.toJson(QJsonDocument::Compact);
        QString result(barray);

        return result;
    }
/**
    CutterAltLog CutterAltLog::parse(const QString json){
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(json.toLocal8Bit(), &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
            if(parse_doucment.isObject())
            {
                QJsonObject obj = parse_doucment.object();
                if(obj.contains("s001") && obj.contains("s002") && obj.contains("s003"))
                {
                    CutterAltLog log;
                    log.setS001(obj.take("s001").toString());
                    log.setS002(obj.take("s002").toString());
                    log.setS003(obj.take("s003").toString());

                    return log;
                }
            }
        }

        return null;
    }
*/
    void CutterAltLog::setS001(QString s){
        s001 =s;
    }

    QString CutterAltLog::getS001(){
        return s001;
    }


    void CutterAltLog::setS002(QString s){
        s002 =s;
    }

    QString CutterAltLog::getS002(){
        return s002;
    }


    void CutterAltLog::setS003(QString s){
        s003 =s;
    }

    QString CutterAltLog::getS003(){
        return s003;
    }
