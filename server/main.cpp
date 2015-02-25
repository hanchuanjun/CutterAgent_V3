/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Solutions component.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>
#include <QDateTime>
#include <QStringList>
#include <QDir>
#include <QSettings>
#include <CutterAgentSvc.h>
#include "log4qt/consoleappender.h"
#include "log4qt/logger.h"
#include "log4qt/ttcclayout.h"
#include "log4qt/basicconfigurator.h"
#include "log4qt/dailyrollingfileappender.h"
#include "log4qt/propertyconfigurator.h"
#include "log4qt/level.h"

#include "qtservice.h"

// HttpDaemon is the the class that implements the simple HTTP server.
class HttpDaemon : public QTcpServer
{
    Q_OBJECT
public:
    HttpDaemon(quint16 port, QObject* parent = 0)
        : QTcpServer(parent), disabled(false)
    {
        listen(QHostAddress::Any, port);
    }

    void incomingConnection(int socket)
    {
        if (disabled)
            return;

        // When a new client connects, the server constructs a QTcpSocket and all
        // communication with the client is done over this QTcpSocket. QTcpSocket
        // works asynchronously, this means that all the communication is done
        // in the two slots readClient() and discardClient().
        QTcpSocket* s = new QTcpSocket(this);
        connect(s, SIGNAL(readyRead()), this, SLOT(readClient()));
        connect(s, SIGNAL(disconnected()), this, SLOT(discardClient()));
        s->setSocketDescriptor(socket);

        QtServiceBase::instance()->logMessage("New Connection");
    }

    void pause()
    {
        disabled = true;
    }

    void resume()
    {
        disabled = false;
    }

private slots:
    void readClient()
    {
        if (disabled)
            return;

        // This slot is called when the client sent data to the server. The
        // server looks if it was a get request and sends a very simple HTML
        // document back.
        QTcpSocket* socket = (QTcpSocket*)sender();
        if (socket->canReadLine()) {
            QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
            if (tokens[0] == "GET") {
                QTextStream os(socket);
                os.setAutoDetectUnicode(true);
                os << "HTTP/1.0 200 Ok\r\n"
                    "Content-Type: text/html; charset=\"utf-8\"\r\n"
                    "\r\n"
                    "<h1>Nothing to see here</h1>\n"
                    << QDateTime::currentDateTime().toString() << "\n";
                socket->close();

                QtServiceBase::instance()->logMessage("Wrote to client");

                if (socket->state() == QTcpSocket::UnconnectedState) {
                    delete socket;
                    QtServiceBase::instance()->logMessage("Connection closed");
                }
            }
        }
    }
    void discardClient()
    {
        QTcpSocket* socket = (QTcpSocket*)sender();
        socket->deleteLater();

        QtServiceBase::instance()->logMessage("Connection closed");
    }

private:
    bool disabled;
};

class CutterAgentService : public QtService<QCoreApplication>
{
public:
    CutterAgentService(int argc, char **argv)
    : QtService<QCoreApplication>(argc, argv, "Cutter Agent Daemon")
    {
        setServiceDescription("An application of Yingroup(V3.0.0,build 2015.2.25), Don't stop it!");
        setServiceFlags(QtServiceBase::CanBeSuspended);
    }

protected:
    void start()
    {
        QCoreApplication *app = application();

        Log4Qt::Logger::logger(QLatin1String("Service"))->info("The service is starting ...!");

        daemon = new CutterAgentSvc();
        daemon->init();


    }

    void processCommand(int code){
        logMessage(QString("Recieve command: %1").arg(code), QtServiceBase::Information);
        Log4Qt::Logger::logger(QLatin1String("Service"))->info(QString("Recieve command: %1").arg(code));

        Log4Qt::Logger *a1 = Log4Qt::Logger::logger("A1");
        if (code <=0){
            a1->setLevel(Log4Qt::Level::OFF_INT);
        }else if (code ==1){
            a1->setLevel(Log4Qt::Level::DEBUG_INT);
        }else if (code ==2){
            a1->setLevel(Log4Qt::Level::INFO_INT);
        }else if (code ==3){
            a1->setLevel(Log4Qt::Level::ERROR_INT);
        }else if (code ==3){
            a1->setLevel(Log4Qt::Level::FATAL_INT);
        }else {
            a1->setLevel(Log4Qt::Level::ALL_INT);
        }
        Log4Qt::Logger::logger(QLatin1String("Service"))->info(QString("info!"));
        Log4Qt::Logger::logger(QLatin1String("Service"))->debug(QString("debug!"));

    }

    void pause()
    {
    //daemon->pause();
    }

    void resume()
    {
    //daemon->resume();
    }

private:
    CutterAgentSvc *daemon;
};

#include "main.moc"

int main(int argc, char **argv)
{
    // Create a layout
/*    Log4Qt::BasicConfigurator::configure();
        Log4Qt::Logger * log = Log4Qt::Logger::rootLogger();

        log->debug("Hello DbZhang800!");
        log->info("Hello Qt!");
        log->warn("Hello 1+1=2");
*/



    QCoreApplication a(argc, argv);
#if !defined(Q_OS_WIN)
    // QtService stores service settings in SystemScope, which normally require root privileges.
    // To allow testing this example as non-root, we change the directory of the SystemScope settings file.
    QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, QDir::tempPath());
    qWarning("(Example uses dummy settings file: %s/QtSoftware.conf)", QDir::tempPath().toLatin1().constData());
#endif
    Log4Qt::PropertyConfigurator::configure(a.applicationDirPath() + "/log.conf");


    Log4Qt::Logger::logger(QLatin1String("main"))->info("The Application is starting ...!");


    CutterAgentService service(argc, argv);
    return service.exec();


/*
    QCoreApplication a(argc, argv);

    Log4Qt::PropertyConfigurator::configure(a.applicationDirPath() + "/log.conf");

    CutterAgentSvc svc;
    svc.init();
    Log4Qt::Logger::logger(QLatin1String("main"))->info("#########################Hello World!");

    return a.exec();
    */
}
