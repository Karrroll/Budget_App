#include "TransactionManager.h"

Transaction TransactionManager::enterTransactionData(TransactionType type) {
    string amount = "";
    Transaction transaction;

    if (type == TransactionType::INCOME)
        transaction.transactionId = incomeFile->getLastId() + 1;

    if (type == TransactionType::EXPENSE)
        transaction.transactionId = expenseFile->getLastId() + 1;

    transaction.userId = getLoggedUserId();
//    transaction.date = getDate();
    cout << "Item: " ;
    while (Utils::inputEmpty(transaction.item = Utils::readLine())) {
        cout << "Try again." << endl;
    }
    cout << "Amount: " ;
    while (true) {
        amount = Utils::readLine();
        replace(amount.begin(), amount.end(), ',', '.');

        if (Utils::validateInput(amount, FieldType::AMOUNT))
            break;

        cout << "Try again." << endl;
    }
    transaction.amount = stod(amount);          //set precision

    return transaction;
}

void TransactionManager::addIncome() {
    Transaction newTransaction = enterTransactionData(TransactionType::INCOME);

    if (!incomeFile->addTransactionToFile(newTransaction)) {
        cout << "Add transaction failed." << endl;
        system("pause");
        return;
    }

    incomes.push_back(newTransaction);
    cout << "Transaction added successfully." << endl;
    system("pause");

}

void TransactionManager::addExpense() {
//    expenseFile->addTransactionToFile();
}
