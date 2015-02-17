#ifndef CUTTERAGENTSVC_H
#define CUTTERAGENTSVC_H

#include <QObject>
#include <Global.h>
#include <processor/CutterSyncPrc.h>


class CutterAgentSvc : public QObject
{
    Q_OBJECT
public:
    explicit CutterAgentSvc(QObject *parent = 0);
    Global *conf;// This is available in all editors.
    void init();
signals:

public slots:
    void showMsg(const QString &msg);
private:
    CutterSyncPrc *licProcessor;
};

#endif // CUTTERAGENTSVC_H
