#pragma once
#include <string>
class Card {
public:
    std::string number;
    std::string pin;
    bool locked;
    int attempts;
    Card(std::string n, std::string p);
    bool verify(std::string input);
};