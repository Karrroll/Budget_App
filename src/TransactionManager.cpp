#include "TransactionManager.h"

TransactionManager::TransactionManager(const int id, const string &incomeFileName, const string &expenseFileName) : LOGGED_USER_ID(id) {
    incomeFile = new TransactionFile(incomeFileName);
    incomes = incomeFile->loadUserTransactionsFromFile(LOGGED_USER_ID);

    expenseFile = new TransactionFile(expenseFileName);
    expenses = expenseFile->loadUserTransactionsFromFile(LOGGED_USER_ID);
}

TransactionManager::~TransactionManager() {
    delete incomeFile;
    delete expenseFile;
}

Transaction TransactionManager::enterTransactionData(TransactionType type) {
    string inputAmountString = "", dateString = "";
    Transaction transaction;

    do {
        dateString = DateMethods::selectDate();
        transaction.date = DateMethods::convertStringDateToInt(dateString);
    } while (transaction.date == 0);

    system("cls");

    if (type == TransactionType::INCOME) {
        cout << "\t<<< NEW INCOME >>>" << endl << endl;
        transaction.transactionId = incomeFile->getLastId() + 1;
    } else if (type == TransactionType::EXPENSE) {
        cout << "\t<<< NEW EXPENSE >>>" << endl << endl;
        transaction.transactionId = expenseFile->getLastId() + 1;
    }

    transaction.userId = LOGGED_USER_ID;
    cout << left << setw(10) << "Date:" << DateMethods::convertToDateWithDashes(dateString) << endl;

    do {
        cout << left << setw(10) << "Item:";
    } while (Utils::inputEmpty(transaction.item = Utils::readLine()));

    do {
        cout << left << setw(10) << "Amount:";
        inputAmountString = Utils::readLine();

        if (!Utils::isValidAmount(inputAmountString)) {
            cout << "Invalid amount (only digits with up to two decimal places)." << endl << endl;
            continue;
        }

        double parsedAmount = Utils::parseAmount(inputAmountString);

        if (parsedAmount <= 0) {
            cout << "Amount must be greater than zero." << endl << endl;
            continue;
        }

        transaction.amount = parsedAmount;
        break;
    } while (true);

    return transaction;
}

pair <int, int> TransactionManager::getStartAndEndDates(BalanceType balanceType) {
    int startDate = 0, endDate = 0;

    auto createDate = [](const int y, const int m, const int d) {
        int date = (y * 100 + m) * 100 + d;
        return DateMethods::validateDate(to_string(date)) ? date : 0;
    };

    if (balanceType == BalanceType::CUSTOM_PERIOD) {
        cout << "\nDATE FROM: ";
        do {
            startDate = DateMethods::convertStringDateToInt(DateMethods::getUserSelectedDate());
        } while (startDate == 0);

        cout << "\nDATE TO: ";
        do {
            endDate = DateMethods::convertStringDateToInt(DateMethods::getUserSelectedDate());
            if (endDate < startDate && endDate != 0) {
                cout << "\nDate cannot be earlier than start date. Try again." << endl;
                system("pause");
                endDate = 0;
            }
        } while (endDate == 0);

        return {startDate, endDate};
    } else {
        //For CURRENT_MONTH or PREVIOUS_MONTH
        const int TODAY_DATE = stoi(DateMethods::getTodayDate());
        const int FIRST_DAY_OF_MONTH = 1;
        const int FIRST_MONTH_OF_YEAR = 1;
        const int LAST_MONTH_OF_YEAR = 12;
        const int CURRENT_YEAR_MONTH_DATE = TODAY_DATE / 100;

        int year = CURRENT_YEAR_MONTH_DATE / 100;
        int month = CURRENT_YEAR_MONTH_DATE % 100;

        if (balanceType == BalanceType::PREVIOUS_MONTH) {
            if (month == FIRST_MONTH_OF_YEAR) {
                year--;
                month = LAST_MONTH_OF_YEAR;
            } else {
                month--;
            }
        }

        int lastDayOfMonth = DateMethods::getDaysInMonth(year, month);
        startDate = createDate(year, month, FIRST_DAY_OF_MONTH);

        if (startDate == 0)
            return {0, 0};

        if (balanceType == BalanceType::PREVIOUS_MONTH)
            endDate = createDate(year, month, lastDayOfMonth);
        else if (balanceType == BalanceType::CURRENT_MONTH && DateMethods::validateDate(to_string(TODAY_DATE)))
            endDate = TODAY_DATE;
        else {
            cout << "Invalid date. Cannot determine end date." << endl;
            system("pause");
            return {0, 0};
        }

        return {startDate, endDate};
    }
}

void TransactionManager::sortTransactionsByDate(vector <Transaction> &transactions) {
    sort(transactions.begin(), transactions.end(), [](const Transaction &a, const Transaction &b) {
        return a.date < b.date;
    });
}

vector <Transaction> TransactionManager::filteredTransactionsByDate(const vector <Transaction> &transactions, const int startDate, const int endDate) {
    vector <Transaction> filteredTransactions;

    for (const auto &transaction: transactions) {
        if (transaction.date >= startDate && transaction.date <= endDate)
            filteredTransactions.push_back(transaction);
    }

    return filteredTransactions;
}

double TransactionManager::calculateTotalTransactionsAmount(const vector <Transaction> &transactions) {
    double totalAmount = 0.0;

    for (const auto &transaction: transactions)
        totalAmount += transaction.amount;

    return totalAmount;
}

void TransactionManager::showTransactions(const vector <Transaction> &transactions, TransactionType type) {
    for (const auto &transaction: transactions) {
        string date = DateMethods::convertToDateWithDashes(to_string(transaction.date));

        cout << "Transaction ID: " << transaction.transactionId << "\tDate: " << date << endl;
        cout << "Item: " << transaction.item << endl;
        cout << "Amount: " << fixed << setprecision(2) << (type == TransactionType::INCOME ? transaction.amount : -transaction.amount) << endl << endl;
    }
}

void TransactionManager::showBalance(const int startDate, const int endDate) {
    system("cls");
    cout << "\t<<< BALANCE OVERVIEW >>>" << endl << endl;

    cout << "INCOME TRANSACTIONS:" << endl;
    vector <Transaction> filteredIncomeTransactions = filteredTransactionsByDate(incomes, startDate, endDate);

    if (!filteredIncomeTransactions.empty()) {
        sortTransactionsByDate(filteredIncomeTransactions);
        showTransactions(filteredIncomeTransactions, TransactionType::INCOME);
    } else {
        cout << "No income transactions found in the selected period." << endl << endl;
    }

    cout << "EXPENSE TRANSACTIONS:" << endl;
    vector <Transaction> filteredExpenseTransactions = filteredTransactionsByDate(expenses, startDate, endDate);

    if (!filteredExpenseTransactions.empty()) {
        sortTransactionsByDate(filteredExpenseTransactions);
        showTransactions(filteredExpenseTransactions, TransactionType::EXPENSE);
    } else {
        cout << "No expense transactions found in the selected period." << endl << endl;
    }

    double totalIncomeAmount = calculateTotalTransactionsAmount(filteredIncomeTransactions);
    double totalExpenseAmount = calculateTotalTransactionsAmount(filteredExpenseTransactions);
    showSummaryBalance(totalIncomeAmount, totalExpenseAmount);
}

void TransactionManager::showSummaryBalance(const double income, const double expense) {
    double totalBalance = income - expense;
    cout << string(55, '-') << endl;
    cout << left << setw(24) << "TOTAL INCOME:" << fixed << setprecision(2) << income << endl;
    cout << left << setw(24) << "TOTAL EXPENSE:" << fixed << setprecision(2) << -expense << endl << endl;
    cout << left << setw(24) <<"TOTAL BALANCE:" << fixed << setprecision(2) << totalBalance << endl << endl;
    system("pause");
}

void TransactionManager::addTransaction(TransactionType type) {
    bool success = false;
    Transaction newTransaction = enterTransactionData(type);

    if (type == TransactionType::INCOME)
        success = incomeFile->addTransactionToFile(newTransaction);
    else if (type == TransactionType::EXPENSE)
        success = expenseFile->addTransactionToFile(newTransaction);
    else {
        cout << "\nUnknown transaction type." << endl;
        system ("pause");
        return;
    }

    if (type == TransactionType::INCOME && success) {
        incomes.push_back(newTransaction);
    } else if (type == TransactionType::EXPENSE && success) {
        expenses.push_back(newTransaction);
    } else {
        cout << "\nTransaction add failed." << endl;
        system("pause");
        return;
    }

    cout << "\nTransaction added successfully." << endl;
    system("pause");
}

void TransactionManager::showCurrentMonthBalance() {
    pair <int, int> dates = getStartAndEndDates(BalanceType::CURRENT_MONTH);
    int startDate = dates.first;
    int endDate = dates.second;

    if (startDate == 0 || endDate == 0)
        return;

    showBalance(startDate, endDate);
}

void TransactionManager::showPreviousMonthBalance() {
    pair <int, int> dates = getStartAndEndDates(BalanceType::PREVIOUS_MONTH);
    int startDate = dates.first;
    int endDate = dates.second;

    if (startDate == 0 || endDate == 0)
        return;
    showBalance(startDate, endDate);
}

void TransactionManager::showCustomPeriodBalance() {
    pair <int, int> dates = getStartAndEndDates(BalanceType::CUSTOM_PERIOD);
    int startDate = dates.first;
    int endDate = dates.second;

    if (startDate == 0 || endDate == 0)
        return;

    showBalance(startDate, endDate);
}




