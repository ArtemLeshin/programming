#include "recovery.h"
#include "file_storage.h"
#include <fstream>

void Recovery::execute(Account& a) {
    std::ifstream f("acc.dat", std::ios::binary);
    if (f.good()) {
        f.close(); // Сначала закрываем чтение
        FileStorage::load(a); // Загружаем данные
    } else {
        // Если файла нет — инициализируем начальным балансом
        a.balance = 10000.0;
        a.dailySpent = 0.0;
        FileStorage::save(a); // Создаем файл
    }
}