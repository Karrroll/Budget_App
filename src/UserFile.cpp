#include "UserFile.h"

bool UserFile::addUserDataToFile(const User &user) {
    CMarkup xmlFile;
    if (!isFileExist())
        createNewXmlFileWithRootNode(xmlFile);

    if (!loadXmlFile(xmlFile) || !enterXmlRootNode(xmlFile))
        return false;

    if (!addChildNode(xmlFile))
        return false;

    xmlFile.AddElem("id", to_string(user.id));
    xmlFile.AddElem("firstName", user.firstName);
    xmlFile.AddElem("lastName", user.lastName);
    xmlFile.AddElem("login", user.userName);
    xmlFile.AddElem("password", user.userPassword);

    xmlFile.OutOfElem();

    if (!xmlFile.Save(getFileName())) {
        cout << "Failed to save the XML file: " << getFileName() << endl;
        return false;
    }

    setLastId(user.id);
    return true;
}

bool UserFile::changePasswordInFile(const int userId, const string &newPassword) {
    CMarkup xmlFile;

    if (!loadXmlFile(xmlFile) || !enterXmlRootNode(xmlFile))
        return false;

    while (xmlFile.FindElem(getChildNodeName())) {
        xmlFile.IntoElem();

        if (!xmlFile.FindElem("id")) {
            xmlFile.OutOfElem();
            cout << "\n<id> tag not found in node:" << endl << endl;
            cout << xmlFile.GetSubDoc() << endl;
            cout << "Please check structure of '" << getFileName() << "' file." << endl;
            system("pause");
            return false;
        }

        int currentId = stoi(xmlFile.GetData());
        if (currentId != userId) {
            xmlFile.OutOfElem();
            continue;
        }

        if (!xmlFile.FindElem("password")) {
            xmlFile.OutOfElem();
            cout << "\n<password> tag not found in node:" << endl << endl;
            cout << xmlFile.GetSubDoc() << endl;
            cout << "Please check structure of '" << getFileName() << "' file." << endl;
            system("pause");
            return false;
        }

        xmlFile.SetData(newPassword);
        xmlFile.OutOfElem();
        return xmlFile.Save(getFileName());
    }

    cout << "No child node matching '" << getChildNodeName() << "' found. Please check structure of '" << getFileName() << "' file." << endl;
    return false;
}

vector <User> UserFile::loadUsersFromFile() {
    CMarkup xmlFile;
    vector <User> users;

    if (!isFileExist())
        return users;

    if (loadXmlFile(xmlFile) && enterXmlRootNode(xmlFile)) {
        User user;
        const string userNodeName = getChildNodeName();

        while (xmlFile.FindElem(userNodeName)) {
            xmlFile.IntoElem();

            string idString = getElementData(xmlFile, "id");
            user.firstName = getElementData(xmlFile, "firstName");
            user.lastName = getElementData(xmlFile, "lastName");
            user.userName = getElementData(xmlFile, "login");
            user.userPassword = getElementData(xmlFile, "password");

            xmlFile.OutOfElem();

            if (idString.empty() || user.firstName.empty() || user.lastName.empty() || user.userName.empty() || user.userPassword.empty()) {
                cout << "Failed to load user data:" << endl << endl;
                cout << xmlFile.GetSubDoc() << endl;
                cout << "Please check structure and content of '" << getFileName() << "' file." << endl;
                system("pause");
                exit(1);
            }

            user.id = stoi(idString);
            users.push_back(user);
        }

        if (!users.empty())
            setLastId(user.id);

    } else {
        exit(1);
    }

    return users;
}
