#include "cutterrptparser.h"
#include <QDateTime>
#include <QTextCodec>
CutterRptParser::CutterRptParser()
{
    this->aOpts = 3;
    this->mOpts = 9;
    this->dOpts = 8;
    this->rOpts = 15;
}
void CutterRptParser::parseMonthlyReport(QString &filename,CutterMonthlyRpt *report){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
        //error to open the file
        //return null;
    }else{
        QTextStream in(&file);
        //CutterMonthlyRpt *report = new CutterMonthlyRpt();
        while(!in.atEnd()){
            QString line = in.readLine();
            if (line.startsWith("1")){
                parseMonthlyReportItem(line,*report);
            }
        }
        file.close();
        //return report;
    }
}

void CutterRptParser::parseDailyReport(QString &filename,CutterDailyRpt *report){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
        //error to open the file
        //return null;
    }else{
        QTextStream in(&file);
        //CutterDailyRpt *report = new CutterDailyRpt();
        while(!in.atEnd()){
            QString line = in.readLine();
            if (line.startsWith("2")){
                parseDailyReportItem(line,*report);
            }
        }
        file.close();
        //return report;
    }
}

void CutterRptParser::parseOptLog(QString &filename,CutterOptLog* optLog){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
        //error to open the file
        //return null;
    }else{
        QTextStream in(&file);
        //CutterOptLog* optLog = new CutterOptLog();
        while(!in.atEnd()){
            QString line = in.readLine();
            if (line.startsWith("3")){
                parseOptLogItem(line,*optLog);
            }
        }
        file.close();
        //return optLog;
    }

}
CutterAltLog* CutterRptParser::parseAlrtLog(QString &filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
        //error to open the file
        //return null;
    }else{
        QTextStream in(&file);
        CutterAltLog* alrtLog = new CutterAltLog();
        while(!in.atEnd()){
            QString line = in.readLine();
            if (line.startsWith("7")){
                this->parseAlrtItem(line,*alrtLog);
            }
        }
        file.close();
        return alrtLog;
    }
}

void CutterRptParser::parse1stConf(const QString &str){
    //parse 1st rows
}
void CutterRptParser::parseDailyReportItem(const QString &args,CutterDailyRpt &dReport){
    QStringList strs = args.split(" ",QString::SkipEmptyParts);

    if (strs.length() <= 1){
        return ;
    }
    //QString tag = strs.at(0).data();
    QString value = strs.at(1).toLocal8Bit().data();
    if (args.startsWith("2:001")) {
        dReport.setS001(value);
    } else if (args.startsWith("2:002")) {

        dReport.setS002(value);
    } else if (args.startsWith("2:003")) {
        dReport.setS003(value);

    } else if (args.startsWith("2:004")) {
        dReport.setS004(value);

    } else if (args.startsWith("2:005")) {
        dReport.setS005(value);

    } else if (args.startsWith("2:006")) {
        dReport.setS006(value);

    } else if (args.startsWith("2:007")) {
        dReport.setS007(value);

    } else if (args.startsWith("2:008")) {
        dReport.setS008(value);

    }
}
void CutterRptParser::parseMonthlyReportItem(const QString &args,CutterMonthlyRpt &mReport){
    QStringList strs = args.split(" ",QString::SkipEmptyParts);
    if (strs.length() <= 1){
        return ;
    }
    //QString tag = strs.at(0).data();
    QString value = strs.at(1).toLocal8Bit().data();
    if (args.startsWith("1:001")) {
        mReport.setS001(value);
    } else if (args.startsWith("1:002")) {

        mReport.setS002(value);
    } else if (args.startsWith("1:003")) {
        mReport.setS003(value);

    } else if (args.startsWith("1:004")) {
        mReport.setS004(value);

    } else if (args.startsWith("1:005")) {
        mReport.setS005(value);

    } else if (args.startsWith("1:006")) {
        mReport.setS006(value);

    } else if (args.startsWith("1:007")) {
        mReport.setS007(value);

    } else if (args.startsWith("1:008")) {
        mReport.setS008(value);

    } else if (args.startsWith("1:009")) {
        mReport.setS009(value);

    }

}
void CutterRptParser::parseOptLogItem(const QString &args,CutterOptLog &rpt){
    QStringList strs = args.split(" ",QString::SkipEmptyParts);
    if (strs.length() <= 1){
        if (args.startsWith("3:001")) {
            rpt.setS001("***.cut");
        }else{
            return ;
        }
    }else{
        //QString tag = strs.at(0).data();
        QString value = strs.at(1).toLocal8Bit().data();
        if (args.startsWith("3:001")) {
           // QTextCodec *gbk = QTextCodec::codecForName("gb2312");

           //QTextCodec *utf8 = QTextCodec::codecForName("utf-8");
          // QTextCodec::setCodecForTr(gbk);

           //QString str = utf8->toUnicode(value.toUtf8());
            rpt.setS001("***.cut");

        } else if (args.startsWith("3:002")) {

            rpt.setS002(value);
        } else if (args.startsWith("3:003")) {
            rpt.setS003(value);

        } else if (args.startsWith("3:004")) {
            rpt.setS004(value);

        } else if (args.startsWith("3:005")) {
            rpt.setS005(value);

        } else if (args.startsWith("3:006")) {
            rpt.setS006(value);

        } else if (args.startsWith("3:007")) {
            rpt.setS007(value);

        } else if (args.startsWith("3:008")) {
            rpt.setS008(value);

        } else if (args.startsWith("3:009")) {
            rpt.setS009(value);

        }else if (args.startsWith("3:010")) {
            rpt.setS010(value);

/**        }else if (args.startsWith("3:011")) {
            rpt.setS011(value);

        }else if (args.startsWith("3:012")) {
            rpt.setS012(value);

        }else if (args.startsWith("3:013")) {
            rpt.setS013(value);

        }else if (args.startsWith("3:014")) {
            rpt.setS014(value);

        }else if (args.startsWith("3:015")) {
            rpt.setS015(value);

        }else if (args.startsWith("3:016")) {
            rpt.setS016(value);

        }else if (args.startsWith("3:017")) {
            rpt.setS017(value);

        }else if (args.startsWith("3:018")) {
            rpt.setS018(value);

        }else if (args.startsWith("3:019")) {
            rpt.setS019(value);

        }else if (args.startsWith("3:020")) {
            rpt.setS020(value);

        }else if (args.startsWith("3:021")) {
            rpt.setS021(value);

        }else if (args.startsWith("3:022")) {
            rpt.setS022(value);

        }else if (args.startsWith("3:023")) {
            rpt.setS023(value);

        }else if (args.startsWith("3:024")) {
            rpt.setS024(value);

        }else if (args.startsWith("3:025")) {
            rpt.setS025(value);

        }else if (args.startsWith("3:026")) {
            rpt.setS026(value);

        }else if (args.startsWith("3:027")) {
            rpt.setS027(value);

        }else if (args.startsWith("3:028")) {
            rpt.setS028(value);

        }else if (args.startsWith("3:029")) {
            rpt.setS029(value);

        }else if (args.startsWith("3:030")) {
            rpt.setS030(value);

        }else if (args.startsWith("3:031")) {
            rpt.setS031(value);
**/
        }
    }
}
void CutterRptParser::parseAlrtItem(const QString &args,CutterAltLog &rpt){

    QString value = this->getValue(args);
    if (args.startsWith("7:001")) {
        rpt.setS001(value);
    } else if (args.startsWith("7:002")) {
        rpt.setS002(value);
    } else if (args.startsWith("7:003")) {
        rpt.setS003(value);
    }

}
QString CutterRptParser::getValue(const QString &args){
    QStringList strs = args.split(" ",QString::SkipEmptyParts);

    QString text=args.toLocal8Bit().data();
    if (strs.size() <=1){
        return "";

    }else{
        QString result = strs.at(1).toLocal8Bit().data();
        if (strs.length() >2){
            for (int ii=2;ii<strs.size();ii++){
                result= result.append(" ").append(strs.at(ii).toLocal8Bit().data());
            }
        }
        return result;
    }

}
