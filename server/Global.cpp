#include "Global.h"
#include "QSettings"
#include "QProcess"
#include <QDebug>

Global::Global(){

}

void Global::init(){
    this->eid=1001000000;
    //取系统环境变量
    QStringList environment = QProcess::systemEnvironment();
    QString str,ygdir="d:\\nip\\",host="http://e-service.yingroup.com:808/DeviceManager/";

    QSettings *reg = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Yingroup\\CutterAgent",
                         QSettings::NativeFormat);
    ygdir = reg->value("cuttercontrolpath","").toString();
    foreach(str,environment)
    {
        if (str.startsWith("windir=") || str.startsWith("WINDIR="))
        {

            windir=str.mid(7);

            //break;
        }

//        if (str.startsWith("yingroup=")){
//            ygdir=str.mid(10);
//        }
    }
    if (!ygdir.endsWith("\\")){
        ygdir =ygdir +"\\";
    }
    //设置程序运行参数
    this->alrtLogPath = ygdir + "CutterAgent\\";
    this->licPath = ygdir + "CutterAgent\\";//windir+"\\system32\\";
    this->rptPath = ygdir+"Nippou\\";
    this->optLogPath = ygdir+"CutterAgent\\";

    //读取注册表，安装时将Cutter的资产id写入到注册表中

    this->assetId = "";
    this->assetId = reg->value("assetid","").toString();
    host=reg->value("server",host).toString();
        delete reg;

    if (!host.endsWith("/")){
        host =host +"/";
    }

    this->instDataPath = host+ "GetVarDataByHttpRequest";
    this->alrtUrl = host+ "EvtmoServlet";
    this->rptUrl = host + "EvtmoServlet";
    this->optLogUrl = host+ "EvtmoServlet";
    this->licUrl = host + "querylicense";
}
