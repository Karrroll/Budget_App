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

    vector <Transaction> incomes;
    vector <Transaction> expenses;

    TransactionFile *incomeFile;
    TransactionFile *expenseFile;

    Transaction enterTransactionData(TransactionType type);
    pair <int, int> getStartAndEndDates(BalanceType balanceType);
    void sortTransactionsByDate(vector <Transaction> &transactions);
    vector <Transaction> filteredTransactionsByDate(const vector <Transaction> &transactions, const int startDate, const int endDate);
    double calculateTotalTransactionsAmount(const vector <Transaction> &transactions);
    void showTransactions(const vector <Transaction> &transactions, TransactionType type);
    void showBalance(const int startDate, const int endDate);
    void showSummaryBalance(const double income, const double expense);

public:
    TransactionManager(const int id, const string &incomeFileName, const string &expenseFileName);
    ~TransactionManager();

    void addTransaction(TransactionType type);
    void showCurrentMonthBalance();
    void showPreviousMonthBalance();
    void showCustomPeriodBalance();
};

#endif // TRANSACTIONMANAGER_H
