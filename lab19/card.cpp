#include "card.h"
Card::Card(std::string n, std::string p) : number(n), pin(p), locked(false), attempts(0) {}
bool Card::verify(std::string input) {
    if(locked) return false;
    if(input == pin) { attempts = 0; return true; }
    if(++attempts >= 3) locked = true;
    return false;
}