#ifndef CUTTERAGENTSVC_H
#define CUTTERAGENTSVC_H

#include <QObject>
#include <Global.h>
#include <processor/CutterSyncPrc.h>
#include <processor/CutterAltPrc.h>
#include <processor/CutterOptPrc.h>
#include "log4qt/consoleappender.h"
#include "log4qt/logger.h"
#include "log4qt/ttcclayout.h"
#include "log4qt/propertyconfigurator.h"


class CutterAgentSvc : public QObject
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER
public:
    explicit CutterAgentSvc(QObject *parent = 0);
    Global *conf;// This is available in all editors.
    void init();
signals:

public slots:
    void showMsg(const QString &msg);
private:
    CutterSyncPrc *licProcessor;
    CutterAltPrc *altProcessor;
    CutterOptPrc *optProcessor;
};

#endif // CUTTERAGENTSVC_H
