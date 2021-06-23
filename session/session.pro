TEMPLATE = app

TARGET = booster-silica-session

INSTALLS += target

target.path = /usr/libexec/mapplauncherd/

CONFIG += link_pkgconfig
PKGCONFIG += applauncherd

SOURCES += booster-session.cpp

