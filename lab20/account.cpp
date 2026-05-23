#include "account.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

Account::Account() : balance(0), dailyWithdrawn(0), lastResetDate("") {}

Account::Account(const std::string& cardNum, double initialBalance) 
    : cardNumber(cardNum), balance(initialBalance), dailyWithdrawn(0) {
    lastResetDate = getCurrentDate();
}

std::string Account::getCurrentDate() {
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(t, "%Y-%m-%d");
    return oss.str();
}

void Account::checkAndResetDailyLimit() {
    std::string today = getCurrentDate();
    if (lastResetDate != today) {
        dailyWithdrawn = 0;
        lastResetDate = today;
        std::cout << "🔄 Суточный лимит сброшен" << std::endl;
    }
}

std::string Account::getCardNumber() const { return cardNumber; }
double Account::getBalance() const { return balance; }
double Account::getDailyWithdrawn() const { return dailyWithdrawn; }

bool Account::canWithdraw(double amount) const {
    double fee = amount * 0.01;
    if (fee < 30) fee = 30;
    double totalWithdraw = amount + fee;
    
    if (amount > 10000) {
        std::cout << "❌ Сумма превышает 10 000 руб за раз!" << std::endl;
        return false;
    }
    if (dailyWithdrawn + amount > 50000) {
        std::cout << "❌ Суточный лимит 50 000 руб превышен!" << std::endl;
        return false;
    }
    if (balance < totalWithdraw) {
        std::cout << "❌ Недостаточно средств! Нужно: " << totalWithdraw << " руб (включая комиссию)" << std::endl;
        return false;
    }
    return true;
}

void Account::withdraw(double amount) {
    checkAndResetDailyLimit();
    
    double fee = amount * 0.01;
    if (fee < 30) fee = 30;
    double totalWithdraw = amount + fee;
    
    if (canWithdraw(amount)) {
        balance -= totalWithdraw;
        dailyWithdrawn += amount;
        std::cout << "✅ Снято: " << amount << " руб" << std::endl;
        std::cout << "💰 Комиссия: " << fee << " руб" << std::endl;
        std::cout << "💰 Новый баланс: " << balance << " руб" << std::endl;
    }
}

void Account::deposit(double amount) {
    balance += amount;
    std::cout << "✅ Пополнено: " << amount << " руб" << std::endl;
    std::cout << "💰 Новый баланс: " << balance << " руб" << std::endl;
}

void Account::addDailyWithdrawn(double amount) {
    dailyWithdrawn += amount;
}

void Account::saveToFile() const {
    std::ofstream file("data/accounts/" + cardNumber + ".txt");
    if (file) {
        file << balance << std::endl;
        file << dailyWithdrawn << std::endl;
        file << lastResetDate << std::endl;
        std::cout << "💾 Баланс сохранён в файл: " << balance << " руб" << std::endl;
    }
}

Account Account::loadFromFile(const std::string& cardNumber) {
    Account acc;
    acc.cardNumber = cardNumber;
    std::ifstream file("data/accounts/" + cardNumber + ".txt");
    if (file) {
        file >> acc.balance;
        file >> acc.dailyWithdrawn;
        file >> acc.lastResetDate;
        std::cout << "📁 Баланс загружен из файла: " << acc.balance << " руб" << std::endl;
    } else {
        acc.balance = 10000;
        acc.dailyWithdrawn = 0;
        acc.lastResetDate = acc.getCurrentDate();
        std::cout << "🆕 Создан новый счёт с балансом: 10000 руб" << std::endl;
    }
    return acc;
}
