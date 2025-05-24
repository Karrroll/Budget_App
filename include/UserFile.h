#ifndef USERFILE_H
#define USERFILE_H

#include <iostream>

#include "File.h"

using namespace std;

class UserFile : public File {
public:
    UserFile(string userFileName) : File(userFileName) {};


};

#endif // USERFILE_H
