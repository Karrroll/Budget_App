#ifndef USERFILE_H
#define USERFILE_H

#include <iostream>
#include <vector>

#include "File.h"
#include "User.h"

using namespace std;

class UserFile : public File {
public:
    UserFile(const string &userFileName) : File(userFileName, "Users", "User") {};

    bool addUserDataToFile(const User &user);
    bool changePasswordInFile(const int userId, const string &newPassword);
    vector <User> loadUsersFromFile();
};

#endif // USERFILE_H
