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
//    transaction.date = getDate();
    cout << "Item: " ;
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
    Transaction newTransaction = enterTransactionData(TransactionType::INCOME);
}

void TransactionManager::addExpense() {
    Transaction newTransaction = enterTransactionData(TransactionType::EXPENSE);
}
