#include "atm_engine.h"
int main() {
    srand(time(0)); // Для рандомных статусов
    ATMEngine atm;
    atm.run();
    return 0;
}