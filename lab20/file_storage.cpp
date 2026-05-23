#include "file_storage.h"
#include <fstream>
#include <iostream>

void FileStorage::saveCard(const Card& card) {
    std::ofstream file("data/cards/" + card.getCardNumber() + ".card");
    if (file) {
        file << card.getCardNumber();
    }
}

Card* FileStorage::loadCard(const std::string& cardNumber) {
    std::ifstream file("data/cards/" + cardNumber + ".card");
    if (file) {
        return new Card(cardNumber, "1234");
    }
    return nullptr;
}

void FileStorage::saveAccount(const Account& account) {
    account.saveToFile();
}

Account FileStorage::loadAccount(const std::string& cardNumber) {
    return Account::loadFromFile(cardNumber);
}
