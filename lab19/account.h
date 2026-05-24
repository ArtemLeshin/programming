#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "transaction.h"

class Account {
private:
    std::string cardNumber;
    double balance;
    double dailyWithdrawn;
    std::string lastResetDate;
    
    void checkAndResetDailyLimit();
    std::string getCurrentDate();
    
public:
    Account();
    Account(const std::string& cardNumber, double initialBalance = 0);
    
    std::string getCardNumber() const;
    double getBalance() const;
    double getDailyWithdrawn() const;
    
    bool canWithdraw(double amount) const;
    void withdraw(double amount);
    void deposit(double amount);
    void addDailyWithdrawn(double amount);
    
    void saveToFile() const;
    static Account loadFromFile(const std::string& cardNumber);
};

#endif