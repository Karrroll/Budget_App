#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

#include "Markup.h"

using namespace std;

class File {

protected:
    const string FILE_NAME;
    CMarkup xmlFile;
    bool isFileExist();
    bool loadXmlFile();
    bool enterXmlRootNode();
    void createNewXmlFileWithRootNode();
    void addChildNode();

private:
    const string ROOT_NODE_NAME;
    const string CHILD_NODE_NAME;

public:
    File(const string &fileName, const string &rootNodeName, const string &childNodeName) : FILE_NAME(fileName), ROOT_NODE_NAME(rootNodeName), CHILD_NODE_NAME(childNodeName) {};
};


#endif // FILE_H
