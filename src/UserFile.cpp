#include "UserFile.h"

bool UserFile::addUserDataToFile(const User &user) {
    CMarkup xmlFile;
    if (!isFileExist())
        createNewXmlFileWithRootNode(xmlFile);

    if (loadXmlFile(xmlFile) && enterXmlRootNode(xmlFile)) {
        addChildNode(xmlFile);

        xmlFile.AddElem("id", to_string(user.id));
        xmlFile.AddElem("firstName", user.firstName);
        xmlFile.AddElem("lastName", user.lastName);
        xmlFile.AddElem("login", user.userName);
        xmlFile.AddElem("password", user.userPassword);

        xmlFile.OutOfElem();
    } else {
        return false;
    }

    if (!xmlFile.Save(getFileName())) {
        cout << "Failed to save the XML file: " << getFileName() << endl;
        return false;
    }
    return true;
}

vector <User> UserFile::loadUsersFromFile() {
    CMarkup xmlFile;
    vector <User> users;

    if (!isFileExist())
        return users;

    if (loadXmlFile(xmlFile) && enterXmlRootNode(xmlFile)) {
        const string userNodeName = getChildNodeName();

        while (xmlFile.FindElem(userNodeName)) {
            xmlFile.IntoElem();

            User user;
            string idString = getElementData(xmlFile, "id");
            user.firstName = getElementData(xmlFile, "firstName");
            user.lastName = getElementData(xmlFile, "lastName");
            user.userName = getElementData(xmlFile, "login");
            user.userPassword = getElementData(xmlFile, "password");

            xmlFile.OutOfElem();

            if (idString.empty() || user.firstName.empty() || user.lastName.empty() || user.userName.empty() || user.userPassword.empty()) {
                cout << "Failed to load user data:" << endl;
                cout << xmlFile.GetSubDoc() << endl;
                cout << "Please check structure and content of '" << getFileName() << "' file." << endl;
                system("pause");
                exit(1);
            }

            user.id = stoi(idString);
            users.push_back(user);
        }
    } else {
        exit(1);
    }

    return users;
}
