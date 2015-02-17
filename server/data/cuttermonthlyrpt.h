#ifndef CUTTERMONTHLYRPT_H
#define CUTTERMONTHLYRPT_H
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QObject>

class CutterMonthlyRpt : public QObject
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

public:
    explicit CutterMonthlyRpt(QObject *parent = 0);
    //static CutterMonthlyRpt parse(const QString json);
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
signals:

public slots:

};

#endif // CUTTERMONTHLYRPT_H
