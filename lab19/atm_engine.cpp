#include "atm_engine.h"
#include "file_storage.h"
#include <iostream>
#include <limits>

ATMEngine::ATMEngine() : currentCard(nullptr), currentAccount(nullptr), sessionActive(false) {}

ATMEngine::~ATMEngine() {
    delete currentCard;
    delete currentAccount;
}

double ATMEngine::calculateFee(double amount) {
    double fee = amount * 0.01;
    if (fee < 30) fee = 30;
    return fee;
}

bool ATMEngine::checkWithdrawLimits(double amount) {
    if (amount > 10000) {
        std::cout << "Ошибка: максимальная сумма снятия 10 000 руб за раз!" << std::endl;
        return false;
    }
    
    if (currentAccount->getDailyWithdrawn() + amount > 50000) {
        std::cout << "Ошибка: суточный лимит 50 000 руб превышен!" << std::endl;
        return false;
    }
    
    return true;
}

bool ATMEngine::insertCard(const std::string& cardNumber) {
    currentCard = FileStorage::loadCard(cardNumber);
    if (!currentCard) {
        currentCard = new Card(cardNumber, "1234");
        FileStorage::saveCard(*currentCard);
    }
    
    currentAccount = new Account(FileStorage::loadAccount(cardNumber));
    return true;
}

bool ATMEngine::enterPin(const std::string& pin) {
    if (!currentCard) return false;
    
    if (currentCard->verifyPin(pin)) {
        return true;
    } else {
        std::cout << "Неверный PIN. Осталось попыток: " 
                  << (3 - currentCard->getWrongAttempts()) << std::endl;
        if (currentCard->isBlocked()) {
            std::cout << "Карта заблокирована!" << std::endl;
        }
        return false;
    }
}

void ATMEngine::showMenu() {
    std::cout << "\n=== ATM 2077 ===\n";
    std::cout << "1. Проверить баланс\n";
    std::cout << "2. Снять наличные\n";
    std::cout << "3. Пополнить баланс\n";
    std::cout << "4. История операций\n";
    std::cout << "5. Выход\n";
    std::cout << "Выберите действие: ";
}

void ATMEngine::checkBalance() {
    std::cout << "Ваш баланс: " << currentAccount->getBalance() << " руб" << std::endl;
    
    Transaction t(TransactionType::BALANCE, 0, 0, currentCard->getCardNumber());
    journal.appendTransaction(t);
}

void ATMEngine::withdrawCash() {
    double amount;
    std::cout << "Введите сумму для снятия: ";
    std::cin >> amount;
    
    if (amount <= 0) {
        std::cout << "Неверная сумма!" << std::endl;
        return;
    }
    
    if (!checkWithdrawLimits(amount)) return;
    
    double fee = calculateFee(amount);
    double total = amount + fee;
    
    if (currentAccount->getBalance() >= total) {
        currentAccount->withdraw(amount);
        currentAccount->addDailyWithdrawn(amount);
        
        Transaction t(TransactionType::WITHDRAW, amount, fee, currentCard->getCardNumber());
        journal.appendTransaction(t);
        
        FileStorage::saveAccount(*currentAccount);
        
        std::cout << "Выдано " << amount << " руб" << std::endl;
        std::cout << "Комиссия: " << fee << " руб" << std::endl;
        std::cout << "Остаток: " << currentAccount->getBalance() << " руб" << std::endl;
    } else {
        std::cout << "Недостаточно средств!" << std::endl;
        std::cout << "Нужно: " << total << " руб (с учётом комиссии)" << std::endl;
    }
}

void ATMEngine::depositCash() {
    double amount;
    std::cout << "Введите сумму для пополнения: ";
    std::cin >> amount;
    
    if (amount <= 0) {
        std::cout << "Неверная сумма!" << std::endl;
        return;
    }
    
    currentAccount->deposit(amount);
    
    Transaction t(TransactionType::DEPOSIT, amount, 0, currentCard->getCardNumber());
    journal.appendTransaction(t);
    
    FileStorage::saveAccount(*currentAccount);
    
    std::cout << "Пополнено " << amount << " руб" << std::endl;
    std::cout << "Новый баланс: " << currentAccount->getBalance() << " руб" << std::endl;
}

void ATMEngine::showLastOperations() {
    journal.printLastN(5);
}

void ATMEngine::startSession() {
    if (!currentCard || currentCard->isBlocked()) {
        std::cout << "Карта недействительна или заблокирована!" << std::endl;
        return;
    }
    
    sessionActive = true;
    int choice;
    
    while (sessionActive) {
        showMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1: checkBalance(); break;
            case 2: withdrawCash(); break;
            case 3: depositCash(); break;
            case 4: showLastOperations(); break;
            case 5: endSession(); break;
            default: std::cout << "Неверный выбор!" << std::endl;
        }
    }
}

void ATMEngine::endSession() {
    std::cout << "Спасибо за использование ATM 2077!" << std::endl;
    sessionActive = false;
}