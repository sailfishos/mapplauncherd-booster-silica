/***************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of applauncherd
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <QFileInfo>
#include <QtGlobal>

#include <QQuickView>
#include <QtQml>

#include <QElapsedTimer>

#include "booster-silica.h"
#include "mdeclarativecache.h"
#include "connection.h"
#include "logger.h"
#include "daemon.h"

const string SilicaBooster::m_boosterType = BOOSTER_TYPE;

class SilicaBoosterData : public QObject
{
    Q_OBJECT
public:
    SilicaBoosterData()
        : QObject(), engine(0), component(0)
    {
    }

    ~SilicaBoosterData()
    {
        if (component && component->isLoading())
            Logger::logInfo("SilicaBooster: Preload compilation aborted.");
        delete component;
    }

    void beginPreload(QQmlEngine *engine, const QUrl &url)
    {
        // We don't start immediately. If processes are being started back-to-back
        // there is no point even starting to preload.
        this->engine = engine;
        source = url;
        timer.start(250, this);
    }

protected:
    bool event(QEvent *event)
    {
        if (event->type() == QEvent::Timer && static_cast<QTimerEvent*>(event)->timerId() == timer.timerId()) {
            timer.stop();
            begin();
            return true;
        }

        return false;
    }

private slots:
    void begin()
    {
        Logger::logInfo("SilicaBooster: Initiate asynchronous preload.");
        component = new QQmlComponent(engine, source, QQmlComponent::Asynchronous);
        if (component->isLoading()) {
            QObject::connect(component, &QQmlComponent::statusChanged,
                             this, &SilicaBoosterData::statusChanged);
        } else {
            statusChanged();
        }
    }

    void statusChanged()
    {
        if (component->isError()) {
            Logger::logError("SilicaBooster: Preload component failed to load:");
            foreach (const QQmlError &e, component->errors())
                Logger::logError("SilicaBooster:    %s", e.toString().toLatin1().constData());
        } else {
            QQmlContext context(engine);
            QObject *obj = component->create(&context);
            if (obj)
                obj->setParent(this);
            else
                Logger::logError("SilicaBooster: Preload object creation failed");
            delete obj;
        }
        // Don't destroy the component here to ensure the components remain in cache
        // until the app loads.
    }

private:
    QBasicTimer timer;
    QQmlEngine *engine;
    QQmlComponent *component;
    QUrl source;
};



SilicaBooster::SilicaBooster()
    : Booster(), data(new SilicaBoosterData)
{
}

SilicaBooster::~SilicaBooster()
{
    delete data;
}

const string & SilicaBooster::boosterType() const
{
    return m_boosterType;
}

bool SilicaBooster::preload()
{
    // for performance reasons, and transparent covers
    QQuickWindow::setDefaultAlphaBuffer(true);

    QQuickView *view = MDeclarativeCache::populate();

    // Load a QML file that references common elements, which will compile and cache them all
    QString file = "/usr/share/booster-";
    file += boosterType().c_str();
    file += "/preload.qml";

    data->beginPreload(view->engine(), QUrl::fromLocalFile(file));

    return true;
}

bool SilicaBooster::receiveDataFromInvoker(int socketFd)
{
    // Use the default implementation if in boot mode
    // (it won't require QApplication running).

    if (bootMode()) {
        return Booster::receiveDataFromInvoker(socketFd);
    } else {
        // Setup the conversation channel with the invoker.
        setConnection(new Connection(socketFd));

        EventHandler handler(this);
        handler.runEventLoop();

        // Destroy preload data, potentially aborting async preload.
        delete data;
        data = 0;

        if (!connection()->connected()) {
            return false;
        }

        // Receive application data from the invoker
        if (!connection()->receiveApplicationData(appData())) {
            connection()->close();
            return false;
        }

        // Close the connection if exit status doesn't need
        // to be sent back to invoker
        if (!connection()->isReportAppExitStatusNeeded()) {
            connection()->close();
        }

        return true;
    }
}


void SilicaBooster::preinit()
{
    QString appName = QFileInfo(m_appData->argv()[0]).fileName();

    QString appClass = appName.left(1).toUpper();
    if (appName.length() > 1)
        appClass += appName.right(appName.length() - 1);

    // char* app_name = qstrdup(appName.toLatin1().data());
    // QApplication::setAppName(app_name);

    // char* app_class = qstrdup(appClass.toLatin1().data());
    // QApplication::setAppClass(app_class);
}

int main(int argc, char **argv)
{
    SilicaBooster *booster = new SilicaBooster;
    Daemon d(argc, argv);
    d.run(booster);
    return 0;
}

#include "booster-silica.moc"
