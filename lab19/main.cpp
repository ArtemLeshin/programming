#include "atm_engine.h"
#include "recovery.h"
#include <iostream>
#include <limits>
#include <cstdio>

int main() {
    std::cout << "\n╔════════════════════════════════════════╗\n";
    std::cout << "║     ДОБРО ПОЖАЛОВАТЬ В ATM 2077     ║\n";
    std::cout << "║     Киберпанк банкинг с вайбом      ║\n";
    std::cout << "╚════════════════════════════════════════╝\n\n";
    
    ATMEngine atm;
    std::string cardNumber, pin;
    int attempts = 0;
    
    std::cout << "💳 Введите номер карты: ";
    std::cin >> cardNumber;
    
    atm.insertCard(cardNumber);
    
    // ========== ВОССТАНОВЛЕНИЕ ПОСЛЕ КРАША ==========
    if (Recovery::needsRecovery()) {
        std::cout << "\n⚠️ [СИСТЕМА] Обнаружено аварийное завершение последней сессии!\n";
        std::cout << "⚠️ [СИСТЕМА] Восстанавливаю баланс из журнала транзакций...\n";
        
        Account recoveredAccount = Recovery::recoverBalance(cardNumber);
        recoveredAccount.saveToFile();
        
        // Обновляем аккаунт в ATMEngine после восстановления
        atm.updateAccount(recoveredAccount);
        
        std::cout << "✅ [СИСТЕМА] Баланс успешно восстановлен: " 
                  << recoveredAccount.getBalance() << " руб\n\n";
    }
    // ===============================================
    
    while (attempts < 3) {
        std::cout << "🔐 Введите PIN: ";
        std::cin >> pin;
        
        if (atm.enterPin(pin)) {
            std::cout << "🔓 Доступ разрешён!\n";
            
            // Сохраняем флаг перед началом сессии
            Recovery::backupBalance(*atm.getCurrentAccount());
            
            atm.startSession();
            
            // После успешного завершения сессии — удаляем флаг краша
            std::remove("recovery.flag");
            break;
        }
        attempts++;
        
        if (attempts >= 3) {
            std::cout << "🔒 КАРТА ЗАБЛОКИРОВАНА. Обратитесь в банк.\n";
        }
    }
    
    std::cout << "\n💀 Спасибо, что выбрали NeuralBank. Ждём вас снова!\n";
    return 0;
}
