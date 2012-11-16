#ifndef JOLLABOOSTER_H
#define JOLLABOOSTER_H

#include "eventhandler.h"
#include "booster.h"

class JollaBooster : public Booster
{
public:
    static const std::string &socketName();

    static const std::string &temporaryProcessName();
    virtual const std::string &boosterTemporaryProcessName() const;
    virtual char boosterType() const { return type(); }
    static char type();
    virtual bool preload();

protected:
    virtual const std::string &socketId() const;
    virtual bool receiveDataFromInvoker(int socketFd);
    virtual void preinit();

private:
    static const std::string m_socketId;
    static const std::string m_temporaryProcessName;
};

#endif
