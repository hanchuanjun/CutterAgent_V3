TARGET   = httpservice
TEMPLATE = app
CONFIG   += console qt
QT = core network 

SOURCES  = main.cpp


include(../../qt-solutions/qtservice/src/qtservice.pri)

