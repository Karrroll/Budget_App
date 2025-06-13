#include "TransactionFile.h"

bool TransactionFile::addTransactionToFile(const Transaction &transaction) {
    CMarkup xmlFile;
    if (!isFileExist())
        createNewXmlFileWithRootNode(xmlFile);

    if (loadXmlFile(xmlFile) && enterXmlRootNode(xmlFile)) {
        addChildNode(xmlFile);

        xmlFile.AddElem("TransactionId", to_string(transaction.transactionId));
        xmlFile.AddElem("userId", to_string(transaction.userId));
        xmlFile.AddElem("date", to_string(transaction.date));
        xmlFile.AddElem("item", transaction.item);
        xmlFile.AddElem("amount", Utils::formatAmount(transaction.amount));

        xmlFile.OutOfElem();
    } else {
        return false;
    }

    if (!xmlFile.Save(getFileName())) {
        cout << "Failed to save the XML file: " << getFileName() << endl;
        return false;
    }

    setLastId(transaction.transactionId);
    return true;
}

