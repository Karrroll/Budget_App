#include "TransactionFile.h"

bool TransactionFile::addTransactionToFile(const Transaction &transaction) {
    CMarkup transactionXmlFile;
    if (!isFileExist())
        createNewXmlFileWithRootNode(transactionXmlFile);

    if (!loadXmlFile(transactionXmlFile) || !enterXmlRootNode(transactionXmlFile))
        return false;

    if (!addChildNode(transactionXmlFile))
        return false;

    transactionXmlFile.AddElem("transactionId", to_string(transaction.transactionId));
    transactionXmlFile.AddElem("userId", to_string(transaction.userId));
    transactionXmlFile.AddElem("date", to_string(transaction.date));
    transactionXmlFile.AddElem("item", transaction.item);
    transactionXmlFile.AddElem("amount", Utils::formatAmount(transaction.amount));

    transactionXmlFile.OutOfElem();

    if (!transactionXmlFile.Save(getFileName())) {
        cout << "Failed to save the XML file: " << getFileName() << endl;
        return false;
    }

    setLastId(transaction.transactionId);
    return true;
}

vector <Transaction> TransactionFile::loadUserTransactionsFromFile(const int userId) {
    CMarkup transactionXmlFile;
    int lastTransactionIdInFile = 0;
    vector <Transaction> transactions;

    if (!isFileExist())
        return transactions;

    if (!loadXmlFile(transactionXmlFile) || !enterXmlRootNode(transactionXmlFile))
        exit(1);

    Transaction transaction;
    const string transactionNodeName = getChildNodeName();

    while (transactionXmlFile.FindElem(transactionNodeName)) {
        transactionXmlFile.IntoElem();

        string transactionIdString = getElementData(transactionXmlFile, "transactionId");
        string userIdString = getElementData(transactionXmlFile, "userId");
        string dateString = getElementData(transactionXmlFile, "date");
        transaction.item = getElementData(transactionXmlFile, "item");
        string amountString = getElementData(transactionXmlFile, "amount");

        transactionXmlFile.OutOfElem();

        if (transactionIdString.empty() || userIdString.empty() || dateString.empty() || transaction.item.empty() || amountString.empty()) {
            cout << "Failed to load income transaction data:" << endl;
            cout << transactionXmlFile.GetSubDoc() << endl;
            cout << "Please check structure and content of '" << getFileName() << "' file." << endl;
            system("pause");
            exit(1);
        }

        if (stoi(userIdString) == userId) {
            transaction.transactionId = stoi(transactionIdString);
            transaction.userId = stoi(userIdString);
            transaction.date = DateMethods::convertStringDateToInt(dateString);
            transaction.amount = stod(amountString);

            transactions.push_back(transaction);
        }

        lastTransactionIdInFile = stoi(transactionIdString);
    }

    if (lastTransactionIdInFile != 0)
        setLastId(lastTransactionIdInFile);

    return transactions;
}
