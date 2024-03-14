
CONFIG += link_pkgconfig
QT += qml quick concurrent feedback dbus sql waylandclient
PKGCONFIG += mlite5 timed-qt5 gio-2.0 glib-2.0 gmodule-2.0 gobject-2.0 applauncherd

CONFIG += qdeclarative-boostable

# We want booster to have all relocations resolved at startup so they do not turn into private dirty pages within boosted
# applications. This adds a little extra initial memory but saves a lot of pages per app.
QMAKE_LFLAGS += -Wl,-z,now

target.path = /usr/libexec/mapplauncherd/
qml.path = /usr/share/$${TARGET}/

service.path = /usr/lib/systemd/user/

SOURCES += ../src/booster-silica.cpp ../src/eventhandler.cpp
HEADERS += ../src/booster-silica.h ../src/eventhandler.h

