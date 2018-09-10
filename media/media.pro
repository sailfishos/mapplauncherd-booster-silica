TEMPLATE = app

TARGET = booster-silica-media

DEFINES += BOOSTER_TYPE=\\\"silica-media\\\"

CONFIG += \
    sailfish_install_qml
QML_FILES = preload.qml

service.files = $${TARGET}.service

INSTALLS += target qml service

OTHER_FILES += preload.qml

include(../booster-silica.pri)
