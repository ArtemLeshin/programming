#include "atm_engine.h"
#include "journal.h"
#include "recovery.h"
#include "transaction.h"
#include "file_storage.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <thread>
#include <chrono>
#include <sstream>

// Вспомогательная функция для эффекта печати
void ATMEngine::printSlow(const std::string& text) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
    std::cout << std::endl;
}

// Конструктор
ATMEngine::ATMEngine() : card("1234-5678", "1111"), failedAttempts(0) { 
    Recovery::execute(acc); 
}

// Метод для работы с меню (после успешного входа)
void ATMEngine::mainMenu() {
    while (true) {
        int choice;
        printSlow("\n--- МЕНЮ VIBEBANK 2077 ---");
        std::cout << "1. Статус счета\n2. Снять кредиты (Лимит 10к)\n3. Пополнить баланс\n4. Хроники операций\n5. Выход\n>>> ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << ">>> ТЕКУЩИЙ БАЛАНС: " << +acc.balance << " КРЕДИТОВ." << std::endl;
        } 
        else if (choice == 2) {
            double amount;
            printSlow(">>> ВВЕДИТЕ СУММУ ДЛЯ СНЯТИЯ:");
            std::cin >> amount;
            double commission = std::max(30.0, amount * 0.01);
            
            if (amount > 10000) {
                printSlow("!!! ОШИБКА: ЛИМИТ ОПЕРАЦИИ ПРЕВЫШЕН (MAX 10,000). !!!");
            } 
            else if (acc.dailySpent + amount + commission > 50000) {
                printSlow("!!! ОШИБКА: СУТОЧНЫЙ ЛИМИТ (50,000) ПРЕВЫШЕН. !!!");
            }
            else if (acc.balance < (amount + commission)) {
                printSlow("!!! ОШИБКА: НЕХВАТКА КРЕДИТОВ. !!!");
            } 
            else {
                acc.balance -= (amount + commission);
                acc.dailySpent += (amount + commission);
                Journal::log({OpType::WITHDRAW, amount, std::time(nullptr)});
                printSlow(">>> СНЯТИЕ УСПЕШНО.");
                std::stringstream stream;
                stream << ">>> КОМИССИЯ СОСТАВИЛА: " << commission << " КРЕДИТОВ.";
                printSlow(stream.str());
                FileStorage::save(acc);
            }
        } 
        else if (choice == 3) {
            double amount;
            printSlow(">>> ВВЕДИТЕ СУММУ ПОПОЛНЕНИЯ:");
            std::cin >> amount;
            if (amount > 0) {
                acc.balance += amount;
                Journal::log({OpType::DEPOSIT, amount, std::time(nullptr)});
                printSlow(">>> БАЛАНС ОБНОВЛЕН.");
                FileStorage::save(acc);
            }
        } 
        else if (choice == 4) {
            showHistory();
        } 
        else if (choice == 5) {
            printSlow(">>> СЕАНС ЗАВЕРШЕН. ВСЕГО ДОБРОГО.");
            break;
        } 
        else {
            printSlow("!!! ОШИБКА: НЕИЗВЕСТНАЯ КОМАНДА. !!!");
        }
    }
}

// Главный цикл запуска (с проверкой попыток)
void ATMEngine::run() {
    while (failedAttempts < 3) {
        printSlow(">>> ЗАПРОС ИДЕНТИФИКАЦИИ. ВВЕДИТЕ PIN-КОД:");
        std::string pin; 
        std::cin >> pin;

        if (card.verify(pin)) {
            printSlow(">>> ДОСТУП РАЗРЕШЕН. ДОБРО ПОЖАЛОВАТЬ В VIBEBANK 2077.");
            mainMenu();
            return;
        } else {
            failedAttempts++;
            printSlow("!!! ОШИБКА: НЕВЕРНЫЙ PIN-КОД !!!");
            std::cout << ">>> ОСТАЛОСЬ ПОПЫТОК: " << (3 - failedAttempts) << std::endl;
        }
    }
    printSlow("!!! ОШИБКА: ПРЕВЫШЕНО КОЛИЧЕСТВО ПОПЫТОК. КАРТА ЗАБЛОКИРОВАНА. !!!");
}

void ATMEngine::showHistory() {
    auto logs = Journal::readLastFive();
    printSlow("\n--- [ХРОНИКИ ОПЕРАЦИЙ (ПОСЛЕДНИЕ 5)] ---");
    if (logs.empty()) {
        printSlow(">>> ЛОГОВ НЕ ОБНАРУЖЕНО.");
    } else {
        for (const auto& t : logs) {
            printTransactionDetails(t);
        }
    }
    printSlow("----------------------------------------");
}