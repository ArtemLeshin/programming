#include "recovery.h"
#include <fstream>
#include <iostream>

Account Recovery::recoverBalance(const std::string& cardNumber) {
    Journal journal("journal.bin");
    auto transactions = journal.readAllTransactions();
    
    Account acc(cardNumber, 0);
    
    for (const auto& t : transactions) {
        if (t.cardNumber == cardNumber) {
            if (t.type == TransactionType::DEPOSIT) {
                acc.deposit(t.amount);
            } else if (t.type == TransactionType::WITHDRAW) {
                acc.withdraw(t.amount);
            }
        }
    }
    
    std::cout << "Баланс восстановлен: " << acc.getBalance() << " руб" << std::endl;
    return acc;
}

bool Recovery::needsRecovery() {
    std::ifstream file("recovery.flag");
    return file.good();
}

void Recovery::backupBalance(const Account& acc) {
    std::ofstream file("recovery.flag");
    file << acc.getBalance();
}