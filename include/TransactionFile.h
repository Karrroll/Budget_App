#ifndef TRANSACTIONFILE_H
#define TRANSACTIONFILE_H

#include "File.h"
#include "Transaction.h"
#include "Utils.h"

class TransactionFile : public File {
public:
    TransactionFile(const string &transactionFileName) : File(transactionFileName, "Transactions", "Transaction") {};

    bool addTransactionToFile(const Transaction &transaction);
    vector <Transaction> loadIncomesFromFile();
    vector <Transaction> loadExpensesFromFile();
protected:

private:
};

#endif // TRANSACTIONFILE_H
