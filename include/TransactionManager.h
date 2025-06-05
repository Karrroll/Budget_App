#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <iostream>
#include <vector>

#include "TransactionFile.h"
#include "Utils.h"

using namespace std;

class TransactionManager {
private:
    const int LOGGED_USER_ID;
    const string INCOME_FILE_NAME;
    const string EXPENSE_FILE_NAME;

    vector <Transaction> incomes;
    vector <Transaction> expenses;

    TransactionFile *incomeFile;
    TransactionFile *expenseFile;
public:
    TransactionManager(const int id, const string &incomeFileName, const string &expenseFileName) : LOGGED_USER_ID(id), INCOME_FILE_NAME(incomeFileName), EXPENSE_FILE_NAME(expenseFileName) {
        incomeFile = new TransactionFile(INCOME_FILE_NAME);
        expenseFile = new TransactionFile(EXPENSE_FILE_NAME);
    };

    ~TransactionManager() {
        delete incomeFile;
        delete expenseFile;
    }

    int getLoggedUserId() const { return LOGGED_USER_ID; };

    Transaction enterTransactionData(TransactionType transactionType);
    void addIncome();
    void addExpense();
};

#endif // TRANSACTIONMANAGER_H
