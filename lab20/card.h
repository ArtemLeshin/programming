#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
private:
    std::string cardNumber;
    std::string pinHash;
    bool blocked;
    int wrongAttempts;
    
public:
    Card();
    Card(const std::string& number, const std::string& pin);
    
    std::string getCardNumber() const;
    bool verifyPin(const std::string& pin);
    void block();
    bool isBlocked() const;
    int getWrongAttempts() const;
    void resetWrongAttempts();
};

#endif
