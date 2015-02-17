#include "cutterdailyrpt.h"
CutterDailyRpt::CutterDailyRpt(QObject *parent) :
    QObject(parent)
{
}

QString CutterDailyRpt::toString(){
    QJsonObject json ;
    json.insert("s001",s001);
    json.insert("s002",s002);
    json.insert("s003",s003);
    json.insert("s004",s004);
    json.insert("s005",s005);
    json.insert("s006",s006);
    json.insert("s007",s007);
    json.insert("s008",s008);

    QJsonDocument document;
    document.setObject(json);
    QByteArray barray = document.toJson(QJsonDocument::Compact);
    QString result(barray);

    return result;
}
/**
CutterDailyRpt CutterDailyRpt::parse(const QString json){
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(json.toLocal8Bit(), &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            if(obj.contains("s001") && obj.contains("s002") && obj.contains("s003"))
            {
                CutterDailyRpt log;
                log.setS001(obj.take("s001").toString());
                log.setS002(obj.take("s002").toString());
                log.setS003(obj.take("s003").toString());
                log.setS004(obj.take("s004").toString());
                log.setS005(obj.take("s005").toString());
                log.setS006(obj.take("s006").toString());
                log.setS007(obj.take("s007").toString());
                log.setS008(obj.take("s008").toString());

                return log;
            }
        }
    }

    return null;
}
*/
void CutterDailyRpt::setS001(QString s){
    s001 =s;
}

QString CutterDailyRpt::getS001(){
    return s001;
}


void CutterDailyRpt::setS002(QString s){
    s002 =s;
}

QString CutterDailyRpt::getS002(){
    return s002;
}


void CutterDailyRpt::setS003(QString s){
    s003 =s;
}

QString CutterDailyRpt::getS003(){
    return s003;
}


void CutterDailyRpt::setS004(QString s){
    s004 =s;
}

QString CutterDailyRpt::getS004(){
    return s004;
}


void CutterDailyRpt::setS005(QString s){
    s005 =s;
}

QString CutterDailyRpt::getS005(){
    return s005;
}


void CutterDailyRpt::setS006(QString s){
    s006 =s;
}

QString CutterDailyRpt::getS006(){
    return s006;
}


void CutterDailyRpt::setS007(QString s){
    s007 =s;
}

QString CutterDailyRpt::getS007(){
    return s007;
}


void CutterDailyRpt::setS008(QString s){
    s008 =s;
}

QString CutterDailyRpt::getS008(){
    return s008;
}


