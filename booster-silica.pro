TEMPLATE = app
TARGET = booster-silica
QT += declarative

target.path = /usr/libexec/mapplauncherd/
qml.path = /usr/share/booster-silica/
qml.files = preload.qml

service.path = /usr/lib/systemd/user/
service.files = data/booster-silica.service

INSTALLS += target qml service

CONFIG += qdeclarative-boostable
LIBS += -lapplauncherd
INCLUDEPATH += /usr/include/applauncherd/

SOURCES += booster-silica.cpp eventhandler.cpp
HEADERS += booster-silica.h eventhandler.h
OTHER_FILES += preload.qml

