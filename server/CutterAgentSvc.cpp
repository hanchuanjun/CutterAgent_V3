#include "cutteragentsvc.h"

CutterAgentSvc::CutterAgentSvc(QObject *parent) :
    QObject(parent)
{
    conf = new  Global();
    conf->init();
    //printf("conf->licUrl=%s",conf->licUrl);
}

void CutterAgentSvc::init(){

    licProcessor=new CutterSyncPrc(this);
    licProcessor->setGlobal(conf);
    licProcessor->start();



   }



void CutterAgentSvc::showMsg(const QString &msg){

    //cout<<"result:"<<text<<endl;
    printf("result:%s",msg.toLocal8Bit().data());
}
