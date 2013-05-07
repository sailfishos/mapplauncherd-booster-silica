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

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QObject>
#include <QSocketNotifier>
#include <signal.h>
#include <tr1/memory>

using std::tr1::shared_ptr;

class Connection;
class Booster;

class EventHandler : public QObject
{
    Q_OBJECT

public:
    //! \brief Constructor
    EventHandler(Booster* parent);

    //! \brief Destructor
    virtual ~EventHandler();

    void runEventLoop();

    //! UNIX signal handler for SIGHUP
    static void hupSignalHandler(int unused);

    //! Setup UNIX signal handlers
    static bool setupUnixSignalHandlers();

    //! Restore UNIX signal handlers to previous values
    static bool restoreUnixSignalHandlers();

private:

    //! wait for socket connection
    void accept();

    //! Socket pair used to get SIGHUP
    static int m_sighupFd[2];

    //! Socket notifier used for m_sighupFd
    shared_ptr<QSocketNotifier> m_snHup;

    //! Old sigaction struct
    static struct sigaction m_oldSigAction;

    // Parent object
    Booster* m_parent;

private slots:

    //! Qt signal handler for SIGHUP.
    void handleSigHup();

signals:
    void connectionAccepted();
    void connectionRejected();
};

#endif
