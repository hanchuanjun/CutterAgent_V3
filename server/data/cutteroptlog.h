#ifndef CUTTEROPTLOG_H
#define CUTTEROPTLOG_H

#include <QObject>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>

class CutterOptLog : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString s001 READ getS001 WRITE setS001)
    Q_PROPERTY(QString s002 READ getS002 WRITE setS002)
    Q_PROPERTY(QString s003 READ getS003 WRITE setS003)
    Q_PROPERTY(QString s004 READ getS004 WRITE setS004)
    Q_PROPERTY(QString s005 READ getS005 WRITE setS005)
    Q_PROPERTY(QString s006 READ getS006 WRITE setS006)
    Q_PROPERTY(QString s007 READ getS007 WRITE setS007)
    Q_PROPERTY(QString s008 READ getS008 WRITE setS008)
    Q_PROPERTY(QString s009 READ getS009 WRITE setS009)
    Q_PROPERTY(QString s010 READ getS010 WRITE setS010)
/**    Q_PROPERTY(QString s011 READ getS011 WRITE setS011)
    Q_PROPERTY(QString s012 READ getS012 WRITE setS012)
    Q_PROPERTY(QString s013 READ getS013 WRITE setS013)
    Q_PROPERTY(QString s014 READ getS014 WRITE setS014)
    Q_PROPERTY(QString s015 READ getS015 WRITE setS015)
    Q_PROPERTY(QString s016 READ getS016 WRITE setS016)
    Q_PROPERTY(QString s017 READ getS017 WRITE setS017)
    Q_PROPERTY(QString s018 READ getS018 WRITE setS018)
    Q_PROPERTY(QString s019 READ getS019 WRITE setS019)
    Q_PROPERTY(QString s020 READ getS020 WRITE setS020)
    Q_PROPERTY(QString s021 READ getS021 WRITE setS021)
    Q_PROPERTY(QString s022 READ getS012 WRITE setS022)
    Q_PROPERTY(QString s023 READ getS023 WRITE setS023)
    Q_PROPERTY(QString s024 READ getS024 WRITE setS024)
    Q_PROPERTY(QString s025 READ getS025 WRITE setS025)
    Q_PROPERTY(QString s026 READ getS026 WRITE setS026)
    Q_PROPERTY(QString s027 READ getS027 WRITE setS027)
    Q_PROPERTY(QString s028 READ getS028 WRITE setS028)
    Q_PROPERTY(QString s029 READ getS029 WRITE setS029)
    Q_PROPERTY(QString s030 READ getS030 WRITE setS030)
    Q_PROPERTY(QString s031 READ getS031 WRITE setS031)
**/
public:
    explicit CutterOptLog(QObject *parent = 0);
   // static CutterOptLog parse(const QString json);
    QString toString();
    void setS001(QString s);
    QString getS001();
    void setS002(QString s);
    QString getS002();
    void setS003(QString s);
    QString getS003();
    void setS004(QString s);
    QString getS004();
    void setS005(QString s);
    QString getS005();
    void setS006(QString s);
    QString getS006();
    void setS007(QString s);
    QString getS007();
    void setS008(QString s);
    QString getS008();
    void setS009(QString s);
    QString getS009();
    void setS010(QString s);
    QString getS010();
    void setS011(QString s);
  /*  QString getS011();
    void setS012(QString s);
    QString getS012();
    void setS013(QString s);
    QString getS013();
    void setS014(QString s);
    QString getS014();
    void setS015(QString s);
    QString getS015();
    void setS016(QString s);
    QString getS016();
    void setS017(QString s);
    QString getS017();
    void setS018(QString s);
    QString getS018();
    void setS019(QString s);
    QString getS019();
    void setS020(QString s);
    QString getS020();
    void setS021(QString s);
    QString getS021();
    void setS022(QString s);
    QString getS022();
    void setS023(QString s);
    QString getS023();
    void setS024(QString s);
    QString getS024();
    void setS025(QString s);
    QString getS025();
    void setS026(QString s);
    QString getS026();
    void setS027(QString s);
    QString getS027();
    void setS028(QString s);
    QString getS028();
    void setS029(QString s);
    QString getS029();
    void setS030(QString s);
    QString getS030();
    void setS031(QString s);
    QString getS031();
    */
private:
    QString s001;
    QString s002;
    QString s003;
    QString s004;
    QString s005;
    QString s006;
    QString s007;
    QString s008;
    QString s009;
    QString s010;
/**
    QString s011;
    QString s012;
    QString s013;
    QString s014;
    QString s015;
    QString s016;
    QString s017;
    QString s018;
    QString s019;
    QString s020;
    QString s021;
    QString s022;
    QString s023;
    QString s024;
    QString s025;
    QString s026;
    QString s027;
    QString s028;
    QString s029;
    QString s030;
    QString s031;
    **/
signals:

public slots:

};

#endif // CUTTEROPTLOG_H
