#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <iostream>

using namespace std;

class TransactionManager {
private:
    const int LOGGED_USER_ID;
public:
    TransactionManager(const int id, const string &incomeFileName, const string &expenseFileName) : LOGGED_USER_ID(id) {};

};

#endif // TRANSACTIONMANAGER_H
