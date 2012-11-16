TEMPLATE = lib
CONFIG += qt plugin hide_symbols
TARGET = jollabooster
QT += declarative

target.path = /usr/lib/applauncherd/
qml.path = /usr/share/jollabooster/
qml.files = preload.qml
INSTALLS += target qml

LIBS += -lmdeclarativecache
INCLUDEPATH += /usr/include/applauncherd/

SOURCES += jollabooster.cpp pluginfactory.cpp
HEADERS += jollabooster.h
OTHER_FILES += preload.qml

