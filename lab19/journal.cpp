// journal.cpp
#include "journal.h"
#include <fstream>

void Journal::log(Transaction t) {
    // Используем ios::binary, чтобы избежать трансформации символов переноса строки
    std::ofstream f("journal.bin", std::ios::binary | std::ios::app);
    if (f.is_open()) {
        f.write(reinterpret_cast<const char*>(&t), sizeof(Transaction));
        f.close();
    }
}

std::vector<Transaction> Journal::readLastFive() {
    std::ifstream f("journal.bin", std::ios::binary | std::ios::ate);
    if (!f.is_open()) return {};

    std::streampos size = f.tellg();
    long long count = size / sizeof(Transaction);
    long long toRead = (count > 5) ? 5 : count;

    // Смещаемся к началу нужного блока
    f.seekg(size - (toRead * (std::streampos)sizeof(Transaction)));
    
    std::vector<Transaction> res(toRead);
    f.read(reinterpret_cast<char*>(res.data()), toRead * sizeof(Transaction));
    
    return res;
}