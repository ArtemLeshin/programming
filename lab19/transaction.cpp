#include "transaction.h"
#include <iostream>
#include <iomanip>
#include <vector>

void printTransactionDetails(const Transaction& t) {
    static const std::vector<std::string> statuses = {"ЗАШИФРОВАНО", "НЕЙРО-СИНХ", "ВАКУУМ-ОЧИСТКА"};
    std::cout << ">>> [" << (t.type == OpType::DEPOSIT ? "КРЕДИТ" : "ДЕБЕТ") << "] "
              << "СУММА: " << std::fixed << std::setprecision(2) << t.amount 
              << " | СТАТУС: " << statuses[rand() % 3] << std::endl;
}