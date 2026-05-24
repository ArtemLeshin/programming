#ifndef ATM_ENGINE_H
#define ATM_ENGINE_H

#include "card.h"
#include "account.h"
#include "journal.h"
#include <string>

class ATMEngine {
private:
    Card* currentCard;
    Account* currentAccount;
    Journal journal;
    bool sessionActive;
    
    double calculateFee(double amount);
    void showMenu();
    bool checkWithdrawLimits(double amount);
    
public:
    ATMEngine();
    ~ATMEngine();
    
    bool insertCard(const std::string& cardNumber);
    bool enterPin(const std::string& pin);
    void startSession();
    void checkBalance();
    void withdrawCash();
    void depositCash();
    void showLastOperations();
    void endSession();
    
    // Геттер и сеттер для восстановления
    Account* getCurrentAccount() { return currentAccount; }
    void updateAccount(const Account& acc) { 
        if (currentAccount) {
            *currentAccount = acc;
        }
    }
};

#endif
