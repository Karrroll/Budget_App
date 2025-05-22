#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>

#include "UserFile.h"

using namespace std;

class UserManager {
    UserFile userFile;
public:
    UserManager(string userFileName) : userFile(userFileName) {};

};

#endif // USERMANAGER_H
