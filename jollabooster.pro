TEMPLATE = lib
CONFIG += qt plugin hide_symbols
TARGET = jollabooster
QT += declarative

target.path = /usr/lib/applauncherd/
qml.path = /usr/share/jollabooster/
qml.files = preload.qml
INSTALLS += target qml

CONFIG += qdeclarative-boostable
LIBS += -lapplauncherd
INCLUDEPATH += /usr/include/applauncherd/

SOURCES += jollabooster.cpp pluginfactory.cpp eventhandler.cpp
HEADERS += jollabooster.h eventhandler.h
OTHER_FILES += preload.qml

