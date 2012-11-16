#include <QtCore>
#include "jollabooster.h"

extern "C" 
{
    Q_DECL_EXPORT void *create()
    {
        return new JollaBooster;
    }

    Q_DECL_EXPORT char type()
    {
        return JollaBooster::type();
    }

    Q_DECL_EXPORT const char *socketName()
    {
        return JollaBooster::socketName().c_str();
    }

    Q_DECL_EXPORT const char *temporaryProcessName()
    {
        return JollaBooster::temporaryProcessName().c_str();
    }
}
