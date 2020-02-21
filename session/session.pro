TEMPLATE = app

TARGET = booster-silica-session

INSTALLS += target

target.path = /usr/libexec/mapplauncherd/

LIBS += -lapplauncherd
INCLUDEPATH += /usr/include/applauncherd/

SOURCES += booster-session.cpp

CONFIG += link_pkgconfig
PKGCONFIG += libsystemd
