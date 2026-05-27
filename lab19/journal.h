#pragma once
#include "transaction.h"
#include <vector>
class Journal {
public:
    static void log(Transaction t);
    static std::vector<Transaction> readLastFive();
};