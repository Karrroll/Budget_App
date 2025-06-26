#include "TransactionFile.h"

bool TransactionFile::addTransactionToFile(const Transaction &transaction) {
    CMarkup xmlFile;
    if (!isFileExist())
        createNewXmlFileWithRootNode(xmlFile);

    if (!loadXmlFile(xmlFile) || !enterXmlRootNode(xmlFile))
        return false;

    if (!addChildNode(xmlFile))
        return false;

    xmlFile.AddElem("transactionId", to_string(transaction.transactionId));
    xmlFile.AddElem("userId", to_string(transaction.userId));
    xmlFile.AddElem("date", to_string(transaction.date));
    xmlFile.AddElem("item", transaction.item);
    xmlFile.AddElem("amount", Utils::formatAmount(transaction.amount));

    xmlFile.OutOfElem();

    if (!xmlFile.Save(getFileName())) {
        cout << "Failed to save the XML file: " << getFileName() << endl;
        return false;
    }

    setLastId(transaction.transactionId);
    return true;
}

vector <Transaction> TransactionFile::loadUserTransactionsFromFile(const int userId) {
    CMarkup xmlFile;
    int lastTransactionIdInFile = 0;
    vector <Transaction> transactions;

    if (!isFileExist())
        return transactions;

    if (!loadXmlFile(xmlFile) || !enterXmlRootNode(xmlFile))
        exit(1);

    Transaction transaction;
    const string transactionNodeName = getChildNodeName();

    while (xmlFile.FindElem(transactionNodeName)) {
        xmlFile.IntoElem();

        string transactionIdString = getElementData(xmlFile, "transactionId");
        string userIdString = getElementData(xmlFile, "userId");
        string dateString = getElementData(xmlFile, "date");
        transaction.item = getElementData(xmlFile, "item");
        string amountString = getElementData(xmlFile, "amount");

        xmlFile.OutOfElem();

        if (transactionIdString.empty() || userIdString.empty() || dateString.empty() || transaction.item.empty() || amountString.empty()) {
            cout << "Failed to load income transaction data:" << endl;
            cout << xmlFile.GetSubDoc() << endl;
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
