#include "TransactionManager.h"

Transaction TransactionManager::enterTransactionData(TransactionType type) {
    string inputAmountString = "";
    double parsedAmount = 0.0;
    Transaction transaction;

    if (type == TransactionType::INCOME)
        transaction.transactionId = incomeFile->getLastId() + 1;
    else if (type == TransactionType::EXPENSE)
        transaction.transactionId = expenseFile->getLastId() + 1;

    transaction.userId = getLoggedUserId();


    while (transaction.date == 0) {
        transaction.date = DateMethods::convertStringDateToInt(DateMethods::selectDate());
    }

    cout << "Item: ";
    while (Utils::inputEmpty(transaction.item = Utils::readLine())) {
        cout << "Try again." << endl;
    }

    cout << "Amount: ";
    while (true) {
        inputAmountString = Utils::readLine();
        if (Utils::isValidAmount(inputAmountString)) {
            parsedAmount = Utils::parseAmount(inputAmountString);

            if (parsedAmount == 0.0) {
                cout << "Amount must be greater than 0. Try again." << endl;
                continue;
            }

            transaction.amount = parsedAmount;
            break;
        }
        cout << "Invalid amount format (only digits and up to two decimal places)." << endl;
        cout << "Try again." << endl;
    }

    return transaction;
}

void TransactionManager::addIncome() {
    Transaction newIncomeTransaction = enterTransactionData(TransactionType::INCOME);

    if (!incomeFile->addTransactionToFile(newIncomeTransaction)) {
        cout << "Failed to add income transaction." << endl;
    } else {
        incomes.push_back(newIncomeTransaction);
        cout << "Income transaction added successfully." << endl;
    }

    system("pause");
}

void TransactionManager::addExpense() {
    Transaction newExpenseTransaction = enterTransactionData(TransactionType::EXPENSE);

    if (!expenseFile->addTransactionToFile(newExpenseTransaction)) {
        cout << "Failed to add expense transaction." << endl;
    } else {
        expenses.push_back(newExpenseTransaction);
        cout << "Expense transaction added successfully." << endl;
    }

    system("pause");
}

void TransactionManager::showCurrentMonthBalance() {
    system("cls");
    int currentYearMonthTag = stoi(DateMethods::getTodayDate()) / 100;

    vector <Transaction> filteredIncomeTransactions;
    double totalIncomeAmount = 0.0;

    vector <Transaction> filteredExpenseTransactions;
    double totalExpenseAmount = 0.0;

    cout << "INCOME TRANSACTIONS" << endl << endl;

    for (const auto &transaction: incomes) {
        if ((transaction.date / 100) == currentYearMonthTag)
            filteredIncomeTransactions.push_back(transaction);
    }

    sortTransactionsByDate(filteredIncomeTransactions);

    for (const auto &transaction: filteredIncomeTransactions) {
        string date = DateMethods::showDateWithDashes(to_string(transaction.date));

        cout << "Transaction ID: " << transaction.transactionId << "\tDate: " << date << endl;
        cout << "Item: " << transaction.item << endl;
        cout << "Amount: " << fixed << setprecision(2) << transaction.amount << endl << endl;
        totalIncomeAmount += transaction.amount;
    }

    cout << "EXPENSE TRANSACTIONS" << endl << endl;

    for (const auto &transaction: expenses) {
        if ((transaction.date / 100) == currentYearMonthTag)
            filteredExpenseTransactions.push_back(transaction);
    }

    sortTransactionsByDate(filteredExpenseTransactions);

    for (const auto &transaction: filteredExpenseTransactions) {
        string date = DateMethods::showDateWithDashes(to_string(transaction.date));

        cout << "Transaction ID: " << transaction.transactionId << "\tDate: " << date << endl;
        cout << "Item: " << transaction.item << endl;
        cout << "Amount: " << fixed << setprecision(2) << -transaction.amount << endl << endl;
        totalExpenseAmount += transaction.amount;
    }

    showSummaryBalance(totalIncomeAmount, totalExpenseAmount);
}


void TransactionManager::showPreviousMonthBalance() {
    system("cls");
    int currentYearMonthTag = stoi(DateMethods::getTodayDate()) / 100;

    int year = currentYearMonthTag / 100;
    int month = currentYearMonthTag % 100;

    if (month == 1) {
        year -= 1;
        month = 12;
    } else {
        month -= 1;
    }

    int previousYearMonthTag = (year * 100) + month;

    vector <Transaction> filteredIncomeTransactions;
    double totalIncomeAmount = 0.0;

    vector <Transaction> filteredExpenseTransactions;
    double totalExpenseAmount = 0.0;

    cout << "INCOME TRANSACTIONS" << endl << endl;

    for (const auto &transaction: incomes) {
        if ((transaction.date / 100) == previousYearMonthTag)
            filteredIncomeTransactions.push_back(transaction);
    }

    sortTransactionsByDate(filteredIncomeTransactions);

    for (const auto &transaction: filteredIncomeTransactions) {
        string date = DateMethods::showDateWithDashes(to_string(transaction.date));

        cout << "Transaction ID: " << transaction.transactionId << "\tDate: " << date << endl;
        cout << "Item: " << transaction.item << endl;
        cout << "Amount: " << fixed << setprecision(2) << transaction.amount << endl << endl;
        totalIncomeAmount += transaction.amount;
    }

    cout << "EXPENSE TRANSACTIONS" << endl << endl;

    for (const auto &transaction: expenses) {
        if ((transaction.date / 100) == previousYearMonthTag)
            filteredExpenseTransactions.push_back(transaction);
    }

    sortTransactionsByDate(filteredExpenseTransactions);

    for (const auto &transaction: filteredExpenseTransactions) {
        string date = DateMethods::showDateWithDashes(to_string(transaction.date));

        cout << "Transaction ID: " << transaction.transactionId << "\tDate: " << date << endl;
        cout << "Item: " << transaction.item << endl;
        cout << "Amount: " << fixed << setprecision(2) << -transaction.amount << endl << endl;
        totalExpenseAmount += transaction.amount;
    }

    showSummaryBalance(totalIncomeAmount, totalExpenseAmount);
}

void TransactionManager::showCustomPeriodBalance() {
    system("cls");
    int startDate = 0;
    int endDate = 0;

    cout << "Start date" << endl;
    do {
        startDate = stoi(DateMethods::getUserSelectedDate());
    } while (startDate == 0);

    cout << "End date" << endl;
    do {
        endDate = stoi(DateMethods::getUserSelectedDate());
        if (endDate < startDate && endDate != 0) {
            cout << "Date cannot be earlier than start date. Try again." << endl;
            endDate = 0;
        }
    } while (endDate == 0);

    vector <Transaction> filteredIncomeTransactions;
    double totalIncomeAmount = 0.0;

    vector <Transaction> filteredExpenseTransactions;
    double totalExpenseAmount = 0.0;

    cout << "INCOME TRANSACTIONS" << endl << endl;

    for (const auto &transaction: incomes) {
        if (transaction.date >= startDate && transaction.date <= endDate)
            filteredIncomeTransactions.push_back(transaction);
    }

    sortTransactionsByDate(filteredIncomeTransactions);

    for (const auto &transaction: filteredIncomeTransactions) {
        string date = DateMethods::showDateWithDashes(to_string(transaction.date));

        cout << "Transaction ID: " << transaction.transactionId << "\tDate: " << date << endl;
        cout << "Item: " << transaction.item << endl;
        cout << "Amount: " << fixed << setprecision(2) << transaction.amount << endl << endl;
        totalIncomeAmount += transaction.amount;
    }

    cout << "EXPENSE TRANSACTIONS" << endl << endl;

    for (const auto &transaction: expenses) {
        if (transaction.date >= startDate && transaction.date <= endDate)
            filteredExpenseTransactions.push_back(transaction);
    }

    sortTransactionsByDate(filteredExpenseTransactions);

    for (const auto &transaction: filteredExpenseTransactions) {
        string date = DateMethods::showDateWithDashes(to_string(transaction.date));

        cout << "Transaction ID: " << transaction.transactionId << "\tDate: " << date << endl;
        cout << "Item: " << transaction.item << endl;
        cout << "Amount: " << fixed << setprecision(2) << -transaction.amount << endl << endl;
        totalExpenseAmount += transaction.amount;
    }

    showSummaryBalance(totalIncomeAmount, totalExpenseAmount);
}

void TransactionManager::showSummaryBalance(const double income, const double expense) {
    double totalBalance = income - expense;
    cout << "TOTAL INCOME: " << fixed << setprecision(2) << income << endl;
    cout << "TOTAL EXPENSE: " << fixed << setprecision(2) << -expense << endl << endl;
    cout << "TOTAL BALANCE: " << fixed << setprecision(2) << totalBalance << endl;
    system("pause");
}

void TransactionManager::sortTransactionsByDate(vector <Transaction> &transactions) {
    sort(transactions.begin(), transactions.end(), [] (const Transaction &a, const Transaction &b) {
        return a.date < b.date;
    });
}


