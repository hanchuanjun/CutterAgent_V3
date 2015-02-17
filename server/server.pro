TARGET   = httpservice
TEMPLATE = app
CONFIG   += console qt
QT = core network 

SOURCES  = main.cpp \
    CutterAgentSvc.cpp \
    Global.cpp \
    data/cutteraltlog.cpp \
    data/cutterdailyrpt.cpp \
    data/cuttermonthlyrpt.cpp \
    data/cutteroptlog.cpp \
    processor/CutterAltPrc.cpp \
    processor/CutterOptPrc.cpp \
    processor/cutterrptparser.cpp \
    processor/CutterSyncPrc.cpp \
    utilities/Utility.cpp


include(../../qt-solutions/qtservice/src/qtservice.pri)

HEADERS += \
    CutterAgentSvc.h \
    Global.h \
    data/cutteraltlog.h \
    data/cutterdailyrpt.h \
    data/cuttermonthlyrpt.h \
    data/cutteroptlog.h \
    processor/CutterAltPrc.h \
    processor/CutterOptPrc.h \
    processor/cutterrptparser.h \
    processor/CutterSyncPrc.h \
    utilities/Utility.h

