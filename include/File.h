#ifndef FILE_H
#define FILE_H

#include <iostream>

#include "Markup.h"

using namespace std;

class File {
public:
    File(const string &fileName) : FILE_NAME(fileName) {};

private:
    const string FILE_NAME;

protected:
    CMarkup xmlFile;

};

#endif // FILE_H
