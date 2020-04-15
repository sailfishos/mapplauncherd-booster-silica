/***************************************************************************
**
** Copyright (c) 2018 - 2020 Jolla Ltd.
** Copyright (c) 2020 Open Mobile Platform LLC.
**
** All rights reserved.
**
** This file is part of mapplauncherd-booster-silica-qt5
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <QVarLengthArray>

#include <booster.h>
#include <logger.h>
#include <daemon.h>

#include <unistd.h>

namespace {
class SessionBooster : public Booster
{
public:
    bool preload() override { return true; }
    const std::string &boosterType() const override { return m_boosterType; }

    int run(SocketManager *)
    {
        const char ** const argv = appData()->argv();
        const int argc = appData()->argc();
        QVarLengthArray<char *, 16> arguments;
        for (int i = 0; i < argc; ++i) {
            arguments.append(strdup(argv[i]));
        }
        arguments.append(nullptr);

        execv(argv[0], arguments.data());
        return 0;
    }

private:
    static const std::string m_boosterType;
};

}

const string SessionBooster::m_boosterType = "silica-session";

int main(int argc, char **argv)
{
    SessionBooster *booster = new SessionBooster;
    Daemon daemon(argc, argv);

    daemon.run(booster);

    return 0;
}
