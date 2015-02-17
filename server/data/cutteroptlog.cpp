#include "cutteroptlog.h"

CutterOptLog::CutterOptLog(QObject *parent) :
    QObject(parent)
{
}

QString CutterOptLog::toString(){
    QJsonObject json;
    json.insert("s001",s001);
    json.insert("s002",s002);
    json.insert("s003",s003);
    json.insert("s004",s004);
    json.insert("s005",s005);
    json.insert("s006",s006);
    json.insert("s007",s007);
    json.insert("s008",s008);
    json.insert("s009",s009);
    json.insert("s010",s010);

    QJsonDocument document;
    document.setObject(json);
    QByteArray barray = document.toJson(QJsonDocument::Compact);
    QString result(barray);

    return result;
 }

/**
CutterOptLog CutterOptLog::parse(const QString json){
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(json.toLocal8Bit(), &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            if(obj.contains("s001") && obj.contains("s002") && obj.contains("s003"))
            {
                CutterOptLog log;
                log.setS001(obj.take("s001").toString());
                log.setS002(obj.take("s002").toString());
                log.setS003(obj.take("s003").toString());
                log.setS004(obj.take("s004").toString());
                log.setS005(obj.take("s005").toString());
                log.setS006(obj.take("s006").toString());
                log.setS007(obj.take("s007").toString());
                log.setS008(obj.take("s008").toString());
                log.setS009(obj.take("s009").toString());
                log.setS010(obj.take("s010").toString());
                return log;
            }
        }
    }
}

*/


 void CutterOptLog::setS001(QString s){
     s001 =s;
 }

 QString CutterOptLog::getS001(){
     return s001;
 }


 void CutterOptLog::setS002(QString s){
     s002 =s;
 }

 QString CutterOptLog::getS002(){
     return s002;
 }


 void CutterOptLog::setS003(QString s){
     s003 =s;
 }

 QString CutterOptLog::getS003(){
     return s003;
 }


 void CutterOptLog::setS004(QString s){
     s004 =s;
 }

 QString CutterOptLog::getS004(){
     return s004;
 }


 void CutterOptLog::setS005(QString s){
     s005 =s;
 }

 QString CutterOptLog::getS005(){
     return s005;
 }


 void CutterOptLog::setS006(QString s){
     s006 =s;
 }

 QString CutterOptLog::getS006(){
     return s006;
 }


 void CutterOptLog::setS007(QString s){
     s007 =s;
 }

 QString CutterOptLog::getS007(){
     return s007;
 }


 void CutterOptLog::setS008(QString s){
     s008 =s;
 }

 QString CutterOptLog::getS008(){
     return s008;
 }



 void CutterOptLog::setS009(QString s){
     s009 =s;
 }

 QString CutterOptLog::getS009(){
     return s009;
 }


 void CutterOptLog::setS010(QString s){
     s010 =s;
 }

 QString CutterOptLog::getS010(){
     return s010;
 }

/**
 void CutterOptLog::setS011(QString s){
     s011 =s;
 }

 QString CutterOptLog::getS011(){
     return s011;
 }

 void CutterOptLog::setS012(QString s){
     s012 =s;
 }

 QString CutterOptLog::getS012(){
     return s012;
 }

 void CutterOptLog::setS013(QString s){
     s013 =s;
 }

 QString CutterOptLog::getS013(){
     return s013;
 }

 void CutterOptLog::setS014(QString s){
     s014 =s;
 }

 QString CutterOptLog::getS014(){
     return s014;
 }

 void CutterOptLog::setS015(QString s){
     s015 =s;
 }

 QString CutterOptLog::getS015(){
     return s015;
 }


 void CutterOptLog::setS016(QString s){
     s016 =s;
 }

 QString CutterOptLog::getS016(){
     return s016;
 }
 void CutterOptLog::setS017(QString s){
     s017 =s;
 }

 QString CutterOptLog::getS017(){
     return s017;
 }
 void CutterOptLog::setS018(QString s){
     s018 =s;
 }

 QString CutterOptLog::getS018(){
     return s018;
 }
 void CutterOptLog::setS019(QString s){
     s019 =s;
 }

 QString CutterOptLog::getS019(){
     return s019;
 }

 void CutterOptLog::setS020(QString s){
     s020 =s;
 }

 QString CutterOptLog::getS020(){
     return s020;
 }
 void CutterOptLog::setS021(QString s){
     s021 =s;
 }

 QString CutterOptLog::getS021(){
     return s021;
 }

 void CutterOptLog::setS022(QString s){
     s022 =s;
 }

 QString CutterOptLog::getS022(){
     return s022;
 }

 void CutterOptLog::setS023(QString s){
     s023 =s;
 }

 QString CutterOptLog::getS023(){
     return s023;
 }


 void CutterOptLog::setS024(QString s){
     s024 =s;
 }

 QString CutterOptLog::getS024(){
     return s024;
 }

 void CutterOptLog::setS025(QString s){
     s025 =s;
 }

 QString CutterOptLog::getS025(){
     return s025;
 }

 void CutterOptLog::setS026(QString s){
     s026 =s;
 }

 QString CutterOptLog::getS026(){
     return s026;
 }
 void CutterOptLog::setS027(QString s){
     s027 =s;
 }

 QString CutterOptLog::getS027(){
     return s027;
 }


 void CutterOptLog::setS028(QString s){
     s028 =s;
 }

 QString CutterOptLog::getS028(){
     return s028;
 }

 void CutterOptLog::setS029(QString s){
     s029 =s;
 }

 QString CutterOptLog::getS029(){
     return s029;
 }


 void CutterOptLog::setS030(QString s){
     s030 =s;
 }

 QString CutterOptLog::getS030(){
     return s030;
 }

 void CutterOptLog::setS031(QString s){
     s031 =s;
 }

 QString CutterOptLog::getS031(){
     return s031;
 }
**/
