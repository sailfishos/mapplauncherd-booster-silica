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

SOURCES += jollabooster.cpp eventhandler.cpp
HEADERS += jollabooster.h eventhandler.h
OTHER_FILES += preload.qml

