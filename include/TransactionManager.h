#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <iostream>
#include <vector>

#include "TransactionFile.h"
#include "Utils.h"
#include "DateMethods.h"

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
        incomes = incomeFile->loadUserTransactionsFromFile(LOGGED_USER_ID);

        expenseFile = new TransactionFile(EXPENSE_FILE_NAME);
        expenses = expenseFile->loadUserTransactionsFromFile(LOGGED_USER_ID);
    };

    ~TransactionManager() {
        delete incomeFile;
        delete expenseFile;
    }

    int getLoggedUserId() const { return LOGGED_USER_ID; };

    Transaction enterTransactionData(TransactionType type);
    void addIncome();
    void addExpense();
    void showBalance(const int startDate, const int endDate);
    void showCurrentMonthBalance();
    void showPreviousMonthBalance();
    void showCustomPeriodBalance();
    pair <int, int> getStartAndEndDates(BalanceType balanceType);
    vector <Transaction> filteredTransactionsByDate(const vector <Transaction> &transactions, const int startDate, const int endDate);
    void sortTransactionsByDate(vector <Transaction> &transactions);
    void showSummaryBalance(const double income, const double expense);
    void showTransactions(const vector <Transaction> &transactions, TransactionType type);
    double calculateTotalTransactionsAmount(const vector <Transaction> &transactions);
};

#endif // TRANSACTIONMANAGER_H
