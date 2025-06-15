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
