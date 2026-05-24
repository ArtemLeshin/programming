#ifndef RECOVERY_H
#define RECOVERY_H

#include "account.h"
#include "journal.h"
#include <string>

class Recovery {
public:
    static Account recoverBalance(const std::string& cardNumber);
    static bool needsRecovery();
    static void backupBalance(const Account& acc);
};

#endif