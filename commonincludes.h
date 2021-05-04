#ifndef COMMONINCLUDES_H
#define COMMONINCLUDES_H

#pragma once
#include "qtincludes.h"

typedef enum netCommands {
    getOnline = 0,
    loginSuccessful = 1,
    recoverContactList = 2,
    message = 3,
    errorLogin = 4,
    addInContactList = 5,
    successfulAddContact = 6,
    errorAddContact = 7,
    updateContactList = 8
} netCommands ;

QString netCommand[9] = {
    "getOnline",
    "loginSuccessful",
    "recoverContactList",
    "message",
    "errorLogin",
    "addInContactList",
    "successfulAddContact",
    "errorAddContact",
    "updateContactList"
};

#endif // COMMONINCLUDES_H
