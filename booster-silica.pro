TEMPLATE = app

equals(QT_MAJOR_VERSION, 4) {
    TARGET = booster-silica
    QT += declarative
    qml.files = qml/preload.qml
}
equals(QT_MAJOR_VERSION, 5) {
    TARGET = booster-silica-qt5
    QT += qml quick concurrent
    qml.files = qml-qt5/preload.qml
}

CONFIG += qdeclarative-boostable

target.path = /usr/libexec/mapplauncherd/
qml.path = /usr/share/$${TARGET}/

service.path = /usr/lib/systemd/user/
service.files = data/$${TARGET}.service

INSTALLS += target qml service

LIBS += -lapplauncherd
INCLUDEPATH += /usr/include/applauncherd/

SOURCES += src/booster-silica.cpp src/eventhandler.cpp
HEADERS += src/booster-silica.h src/eventhandler.h
OTHER_FILES += qml/preload.qml qml-qt5/preload.qml

