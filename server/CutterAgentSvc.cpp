#include "cutteragentsvc.h"

CutterAgentSvc::CutterAgentSvc(QObject *parent) :
    QObject(parent)
{
    conf = new  Global();
    conf->init();
     logger()->info("------------info---------------------constructor");

    //printf("conf->licUrl=%s",conf->licUrl);
}

void CutterAgentSvc::init(){

    logger()->debug("-------------Debug--------------------constructor");
    licProcessor=new CutterSyncPrc(this);
    licProcessor->setGlobal(conf);
    licProcessor->start();

    altProcessor = new CutterAltPrc(this);
    altProcessor->setGlobal(conf);
    altProcessor->start();

    this->optProcessor = new CutterOptPrc(this);
    optProcessor->setGlobal(conf);
    optProcessor->start();

   }



void CutterAgentSvc::showMsg(const QString &msg){

    //cout<<"result:"<<text<<endl;
    printf("result:%s",msg.toLocal8Bit().data());
}
