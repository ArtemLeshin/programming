#include "card.h"

Card::Card() : cardNumber(""), pinHash(""), blocked(false), wrongAttempts(0) {}

Card::Card(const std::string& number, const std::string& pin) 
    : cardNumber(number), pinHash(pin), blocked(false), wrongAttempts(0) {}

std::string Card::getCardNumber() const { return cardNumber; }

bool Card::verifyPin(const std::string& pin) {
    if (blocked) return false;
    
    if (pin == pinHash) {
        wrongAttempts = 0;
        return true;
    } else {
        wrongAttempts++;
        if (wrongAttempts >= 3) {
            blocked = true;
        }
        return false;
    }
}

void Card::block() { blocked = true; }
bool Card::isBlocked() const { return blocked; }
int Card::getWrongAttempts() const { return wrongAttempts; }
void Card::resetWrongAttempts() { wrongAttempts = 0; }
