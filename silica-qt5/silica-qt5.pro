TEMPLATE = app

TARGET = booster-silica-qt5

DEFINES += BOOSTER_TYPE=\\\"silica-qt5\\\"

qml.files = preload.qml
service.files = $${TARGET}.service
service.files += $${TARGET}@.service

INSTALLS += target qml service

OTHER_FILES += preload.qml

include(../booster-silica.pri)

