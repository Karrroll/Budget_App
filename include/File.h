#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

#include "Markup.h"

using namespace std;

class File {
private:
    const string FILE_NAME;
    const string ROOT_NODE_NAME;
    const string CHILD_NODE_NAME;

public:
    File(const string &fileName, const string &rootNodeName, const string &childNodeName) : FILE_NAME(fileName), ROOT_NODE_NAME(rootNodeName), CHILD_NODE_NAME(childNodeName) {};



protected:
//    CMarkup xmlFile;
//    string getFileName() const { return FILE_NAME; };
//    string getRootNodeName() const { return ROOT_NODE_NAME; };
    string getChildNodeName() const { return CHILD_NODE_NAME; };
    bool isFileExist();
    bool loadXmlFile(CMarkup &xmlFile);
    bool enterXmlRootNode(CMarkup &xmlFile);
    void addChildNode(CMarkup &xmlFile);
};

#endif // FILE_H
