#include "File.h"

#include <iostream>

using namespace std;

bool File::isFileExist() {
    ifstream file(FILE_NAME);
    return file.good();
}
