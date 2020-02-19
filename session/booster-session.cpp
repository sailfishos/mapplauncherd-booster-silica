#include <QVarLengthArray>

#include <booster.h>
#include <logger.h>
#include <daemon.h>

#include <sys/types.h>
#include <systemd/sd-bus.h>
#include <systemd/sd-login.h>
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

/**
 * Set logind session active.
 *
 * Since we don't have a display/login manager, do it here instead.
 * Using libsystemd functions to get session id and there is
 * no Qt mainloop, so using also libsystemd's dbus methods to do
 * the one call that's needed.
 */
static void activateLogindSession()
{
    char *session = NULL;
    sd_bus *bus = NULL;
    sd_bus_message *message = NULL;
    sd_bus_message *reply = NULL;

    if (sd_pid_get_session(getpid(), &session) < 0) {
        Logger::logError("Could not read session id");
        goto END;
    }

    if (sd_bus_default_system(&bus) < 0) {
        Logger::logError("Could not acquire system bus");
        goto END;
    }

    if (sd_bus_message_new_method_call(bus, &message,
                                       "org.freedesktop.login1",
                                       "/org/freedesktop/login1",
                                       "org.freedesktop.login1.Manager",
                                       "ActivateSession") < 0) {
        Logger::logError("Could not create method call");
        goto END;
    }

    if (sd_bus_message_append(message, "s", session) < 0) {
        Logger::logError("Could not append argument");
        goto END;
    }

    if (sd_bus_call(bus, message, -1, NULL, &reply) < 0) {
        Logger::logError("Could not activate session '%s'", session);
        goto END;
    }

    sd_bus_message_read(reply, NULL);

    Logger::logInfo("Activated session '%s'", session);

END:
    free(session);
    sd_bus_unref(bus);
    sd_bus_message_unref(message);
    sd_bus_message_unref(reply);
}

const string SessionBooster::m_boosterType = "silica-session";

int main(int argc, char **argv)
{
    SessionBooster *booster = new SessionBooster;
    Daemon daemon(argc, argv);

    activateLogindSession();

    daemon.run(booster);

    return 0;
}
