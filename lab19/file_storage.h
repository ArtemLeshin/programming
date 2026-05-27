#pragma once
#include "account.h"
class FileStorage {
public:
    static void save(Account& a);
    static void load(Account& a);
};