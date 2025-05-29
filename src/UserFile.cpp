#include "UserFile.h"

vector <User> UserFile::loadUsersFromFile() {
    CMarkup xmlFile;
    User user;
    vector <User> users;

    if (!isFileExist())
        return users;

    if (loadXmlFile(xmlFile) && enterXmlRootNode(xmlFile)) {
        const string userNodeName = getChildNodeName();

        while (xmlFile.FindElem(userNodeName)) {
            xmlFile.IntoElem();

            xmlFile.FindElem("id");
            user.id = stoi(xmlFile.GetData());

            xmlFile.FindElem("firstName");
            user.firstName = xmlFile.GetData();

            xmlFile.FindElem("lastName");
            user.lastName = xmlFile.GetData();

            xmlFile.FindElem("login");
            user.userName = xmlFile.GetData();

            xmlFile.FindElem("password");
            user.userPassword = xmlFile.GetData();

            xmlFile.OutOfElem();
            users.push_back(user);
        }
    }
    return users;
}

