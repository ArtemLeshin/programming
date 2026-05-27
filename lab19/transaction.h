// atm/transaction.h
#pragma once
#include <ctime>
#include <string>

enum class OpType : int { DEPOSIT, WITHDRAW };

#pragma pack(push, 1)
struct Transaction {
    OpType type;
    double amount;
    std::time_t timestamp;
};
#pragma pack(pop)

// Теперь, когда Transaction определен, объявляем функцию
void printTransactionDetails(const Transaction& t);