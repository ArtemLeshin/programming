#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

enum class TransactionType {
    WITHDRAW,
    DEPOSIT,
    BALANCE
};

struct Transaction {
    TransactionType type;
    double amount;
    double fee;
    time_t timestamp;
    std::string cardNumber;
    
    Transaction();
    Transaction(TransactionType t, double a, double f, const std::string& card);
    
    std::string typeToString() const;
    std::string toString() const;
};

#endif