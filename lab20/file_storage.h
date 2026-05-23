#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include "card.h"
#include "account.h"
#include <string>

class FileStorage {
public:
    static void saveCard(const Card& card);
    static Card* loadCard(const std::string& cardNumber);
    
    static void saveAccount(const Account& account);
    static Account loadAccount(const std::string& cardNumber);
};

#endif