#include "journal.h"
#include <fstream>
#include <iostream>

Journal::Journal(const std::string& fname) : filename(fname) {}

void Journal::appendTransaction(const Transaction& t) {
    std::ofstream file(filename, std::ios::binary | std::ios::app);
    if (!file) {
        std::cerr << "Ошибка открытия журнала!" << std::endl;
        return;
    }
    file.write(reinterpret_cast<const char*>(&t), sizeof(Transaction));
}

std::vector<Transaction> Journal::readAllTransactions() {
    std::vector<Transaction> transactions;
    std::ifstream file(filename, std::ios::binary);
    if (!file) return transactions;
    
    Transaction t;
    while (file.read(reinterpret_cast<char*>(&t), sizeof(Transaction))) {
        transactions.push_back(t);
    }
    return transactions;
}

std::vector<Transaction> Journal::getLastN(int n) {
    auto all = readAllTransactions();
    std::vector<Transaction> lastN;
    int start = all.size() > n ? all.size() - n : 0;
    for (int i = start; i < all.size(); i++) {
        lastN.push_back(all[i]);
    }
    return lastN;
}

void Journal::printLastN(int n) {
    auto transactions = getLastN(n);
    std::cout << "\n=== ПОСЛЕДНИЕ " << n << " ОПЕРАЦИЙ ===\n";
    for (const auto& t : transactions) {
        std::cout << t.toString() << std::endl;
    }
    std::cout << "========================\n";
}
