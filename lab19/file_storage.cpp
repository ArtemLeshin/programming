#include "file_storage.h"
#include <fstream>

void FileStorage::save(Account& a) {
    std::ofstream f("acc.dat", std::ios::binary | std::ios::trunc);
    if (f.is_open()) {
        f.write(reinterpret_cast<const char*>(&a), sizeof(Account));
        f.close();
    }
}

void FileStorage::load(Account& a) {
    std::ifstream f("acc.dat", std::ios::binary);
    if (f.is_open()) {
        f.read(reinterpret_cast<char*>(&a), sizeof(Account));
        f.close();
    }
}