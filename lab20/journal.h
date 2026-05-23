#ifndef JOURNAL_H
#define JOURNAL_H

#include "transaction.h"
#include <vector>
#include <string>

class Journal {
private:
    std::string filename;
    
public:
    Journal(const std::string& fname = "journal.bin");
    
    void appendTransaction(const Transaction& t);
    std::vector<Transaction> readAllTransactions();
    std::vector<Transaction> getLastN(int n);
    void printLastN(int n);
};

#endif
