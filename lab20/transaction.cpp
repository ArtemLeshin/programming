#include "transaction.h"
#include <sstream>
#include <iomanip>
#include <ctime>

Transaction::Transaction() : amount(0), fee(0), timestamp(0) {}

Transaction::Transaction(TransactionType t, double a, double f, const std::string& card)
    : type(t), amount(a), fee(f), cardNumber(card) {
    timestamp = time(nullptr);
}

std::string Transaction::typeToString() const {
    switch(type) {
        case TransactionType::WITHDRAW: return "СНЯТИЕ";
        case TransactionType::DEPOSIT: return "ПОПОЛНЕНИЕ";
        case TransactionType::BALANCE: return "ПРОВЕРКА БАЛАНСА";
        default: return "НЕИЗВЕСТНО";
    }
}

std::string Transaction::toString() const {
    std::ostringstream oss;
    struct tm* t = localtime(&timestamp);
    oss << std::put_time(t, "%d.%m.%Y %H:%M:%S");
    oss << " | " << typeToString();
    oss << " | " << amount << " руб";
    if (fee > 0) oss << " (комиссия: " << fee << " руб)";
    return oss.str();
}
