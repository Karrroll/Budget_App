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

void TransactionManager::showBalance(const int startDate, const int endDate) {
    cout << "INCOME TRANSACTIONS" << endl << endl;

    vector <Transaction> filteredIncomeTransactions = filteredTransactionsByDate(incomes, startDate, endDate);
    sortTransactionsByDate(filteredIncomeTransactions);
    showTransactions(filteredIncomeTransactions, TransactionType::INCOME);

    cout << "EXPENSE TRANSACTIONS" << endl << endl;

    vector <Transaction> filteredExpenseTransactions = filteredTransactionsByDate(expenses, startDate, endDate);
    sortTransactionsByDate(filteredExpenseTransactions);
    showTransactions(filteredExpenseTransactions, TransactionType::EXPENSE);

    double totalExpenseAmount = calculateTotalTransactionsAmount(filteredExpenseTransactions);
    double totalIncomeAmount = calculateTotalTransactionsAmount(filteredIncomeTransactions);
    showSummaryBalance(totalIncomeAmount, totalExpenseAmount);
}

void TransactionManager::showCurrentMonthBalance() {
    system("cls");
    pair <int, int> dates = getStartAndEndDates(BalanceType::CURRENT_MONTH);
    int startDate = dates.first;
    int endDate = dates.second;

    if (startDate == 0 || endDate == 0)
        return;

    showBalance(startDate, endDate);
}

void TransactionManager::showPreviousMonthBalance() {
    system("cls");
    pair <int, int> dates = getStartAndEndDates(BalanceType::PREVIOUS_MONTH);
    int startDate = dates.first;
    int endDate = dates.second;

    if (startDate == 0 || endDate == 0)
        return;
    showBalance(startDate, endDate);
}

void TransactionManager::showCustomPeriodBalance() {
    system("cls");
    pair <int, int> dates = getStartAndEndDates(BalanceType::CUSTOM_PERIOD);
    int startDate = dates.first;
    int endDate = dates.second;

    if (startDate == 0 || endDate == 0)
        return;

    showBalance(startDate, endDate);
}

void TransactionManager::showSummaryBalance(const double income, const double expense) {
    double totalBalance = income - expense;
    cout << "TOTAL INCOME: " << fixed << setprecision(2) << income << endl;
    cout << "TOTAL EXPENSE: " << fixed << setprecision(2) << -expense << endl << endl;
    cout << "TOTAL BALANCE: " << fixed << setprecision(2) << totalBalance << endl;
    system("pause");
}

vector <Transaction> TransactionManager::filteredTransactionsByDate(const vector <Transaction> &transactions, const int startDate, const int endDate) {
    vector <Transaction> filteredTransactions;

    for (const auto &transaction: transactions) {
        if (transaction.date >= startDate && transaction.date <= endDate)
            filteredTransactions.push_back(transaction);
    }

    return filteredTransactions;
}

void TransactionManager::sortTransactionsByDate(vector <Transaction> &transactions) {
    sort(transactions.begin(), transactions.end(), [](const Transaction &a, const Transaction &b) {
        return a.date < b.date;
    });
}

void TransactionManager::showTransactions(const vector <Transaction> &transactions, TransactionType type) {
    for (const auto &transaction: transactions) {
        string date = DateMethods::dateWithDashes(to_string(transaction.date));

        cout << "Transaction ID: " << transaction.transactionId << "\tDate: " << date << endl;
        cout << "Item: " << transaction.item << endl;
        cout << "Amount: " << fixed << setprecision(2) << (type == TransactionType::INCOME ? transaction.amount : -transaction.amount) << endl << endl;
    }
}

double TransactionManager::calculateTotalTransactionsAmount(const vector <Transaction> &transactions) {
    double totalAmount = 0.0;

    for (const auto &transaction: transactions)
        totalAmount += transaction.amount;

    return totalAmount;
}

pair <int, int> TransactionManager::getStartAndEndDates(BalanceType balanceType) {
    int startDate = 0, endDate = 0;

    auto createDate = [](const int y, const int m, const int d) {
        int date = (y * 100 + m) * 100 + d;
        return DateMethods::validateDate(to_string(date)) ? date : 0;
    };

    if (balanceType == BalanceType::CUSTOM_PERIOD) {
        cout << "From: " << endl;
        do {
            startDate = DateMethods::convertStringDateToInt(DateMethods::getUserSelectedDate());
        } while (startDate == 0);

        cout << "To: " << endl;
        do {
            endDate = DateMethods::convertStringDateToInt(DateMethods::getUserSelectedDate());
            if (endDate < startDate && endDate != 0) {
                cout << "Date cannot be earlier than start date. Try again." << endl;
                endDate = 0;
            }
        } while (endDate == 0);

        return {startDate, endDate};
    } else {
        const int FIRST_DAY_OF_MONTH = 1;
        const int FIRST_MONTH_OF_YEAR = 1;
        const int LAST_MONTH_OF_YEAR = 12;
        const int CURRENT_YEAR_MONTH_DATE = stoi(DateMethods::getTodayDate()) / 100;

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
        endDate = createDate(year, month, lastDayOfMonth);

        return {startDate, endDate};
    }
}



//void TransactionManager::getBalanceStartDate(int &startDate, int &endDate) {
//    const int FIRST_DAY_OF_MONTH = 1;
//
//    int currentYearMonthDate = stoi(DateMethods::getTodayDate()) / 100;
//    int currentMonth = currentYearMonthDate % 100;
//    int currentYear = currentYearMonthDate / 100;
//
//    if () {
//        int lastDayOfMonth = DateMethods::getDaysInMonth(currentYear, CurrentMonth);
//
//        startDate = (currentYear *100 + currentMonth) * 100 + FIRST_DAY_OF_MONTH;
//        endDate = (currentYear *100 + currentMonth) * 100 + lastDayOfMonth;
//    } else if () {
//        int previousYear = 0;
//        int previousMonth = 0;
//
//        if (currentMonth == 1) {
//            previousMonth = 12;
//            previousYear = currentYear - 1;
//        } else {
//            previousMonth = currentMonth - 1;
//            previousYear = currentYear;
//        }
//        int lastDayOfMonth = DateMethods::getDaysInMonth(previousYear, previousMonth);
//
//        startDate = (previousYear *100 + previousMonth) * 100 + FIRST_DAY_OF_MONTH;
//        endDate = (previousYear *100 + previousMonth) * 100 + lastDayOfMonth;
//    } else if () {
//        cout << "From: " << endl;
//
//        do {
//            startDate = stoi(DateMethods::getUserSelectedDate());
//        } while (startDate == 0);
//
//        cout << "To: " << endl;
//        do {
//            endDate = stoi(DateMethods::getUserSelectedDate());                         // i od dzisiejszej daty czy juz to jest?
//            if (endDate < startDate && endDate != 0) {
//                cout << "Date cannot be earlier than start date. Try again." << endl;
//                endDate = 0;
//            }
//        } while (endDate == 0);
//    }
//}
//
//const int FIRST_DAY_OF_MONTH = 1;
//const int LAST_POSSIBLE_DAY_IN_MONTH = 31;
//
//int currentYearMonthDate = (stoi(DateMethods::getTodayDate()) / 100);
//int startDate = currentYearMonthDate * 100 + FIRST_DAY_OF_MONTH;
//int endDate = currentYearMonthDate * 100 + LAST_POSSIBLE_DAY_IN_MONTH;
//
////    int currentYearMonthTag = stoi(DateMethods::getTodayDate()) / 100;
//
//    vector <Transaction> filteredIncomeTransactions;
//    double totalIncomeAmount = 0.0;
//
//    vector <Transaction> filteredExpenseTransactions;
//    double totalExpenseAmount = 0.0;
//
//    cout << "INCOME TRANSACTIONS" << endl << endl;
//
//    for (const auto &transaction: incomes) {
//        if (transaction.date >= startDate && transaction.date <= endDate)
//            filteredIncomeTransactions.push_back(transaction);
//    }
//
//
//
//    int currentYearMonthDate = stoi(DateMethods::getTodayDate()) / 100;
//
//    int year = currentYearMonthDate / 100;
//    int month = currentYearMonthDate % 100;
//
//    if (month == 1) {
//        year -= 1;
//        month = 12;
//    } else {
//        month -= 1;
//    }
//
//    int previousYearMonthTag = (year * 100) + month;
//
//
//
//    int startDate = 0;
//    int endDate = 0;
//
//    cout << "Start date" << endl;
//    do {
//        startDate = stoi(DateMethods::getUserSelectedDate());
//    } while (startDate == 0);
//
//    cout << "End date" << endl;
//    do {
//        endDate = stoi(DateMethods::getUserSelectedDate());
//        if (endDate < startDate && endDate != 0) {
//            cout << "Date cannot be earlier than start date. Try again." << endl;
//            endDate = 0;
//        }
//    } while (endDate == 0);
