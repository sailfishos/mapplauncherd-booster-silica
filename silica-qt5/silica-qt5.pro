TEMPLATE = app

TARGET = booster-silica-qt5

DEFINES += BOOSTER_TYPE=\\\"silica-qt5\\\"

CONFIG += \
    sailfish_install_qml

QML_FILES = preload.qml

service.files = $${TARGET}.service

INSTALLS += target service

OTHER_FILES += preload.qml

include(../booster-silica.pri)

