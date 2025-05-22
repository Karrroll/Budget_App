#ifndef USERFILE_H
#define USERFILE_H

#include <iostream>

#include "File.h"

using namespace std;

class UserFile {
    File file;
public:
    UserFile(string userFileName) : file(userFileName) {};

};

#endif // USERFILE_H
