TEMPLATE = app

TARGET = booster-silica-media

DEFINES += BOOSTER_TYPE=\\\"silica-media\\\"

qml.files = preload.qml
service.files = $${TARGET}.service

INSTALLS += target qml service

OTHER_FILES += preload.qml

include(../booster-silica.pri)
