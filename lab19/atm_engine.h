#pragma once
#include "card.h"
#include "account.h"
class ATMEngine {
    Account acc;
    Card card;
    void printSlow(const std::string& text); // Добавь эту строку
    int failedAttempts = 0;
    void mainMenu();
public:
    ATMEngine();
    void run();
    void showHistory();
};