#include "Utils.h"

string Utils::getLinie() {
    string input = "";

    getline(cin, input);
    return input;
}

bool Utils::inputEmpty(const string &input) {
    if (input.empty()) {
        cout << "Field cannot be empty." << endl;
        return true;
    }
    return false;
}

bool Utils::containsDigits(const string &input) {
    for (char character : input) {
        if (isdigit(static_cast<unsigned char>(character))) {
            cout << "Field cannot contain digits." << endl;
            return true;
        }
    }
    return false;
}

bool Utils::containsSpaces(const string &input) {
    for (char character : input) {
        if (character == ' ') {
            cout << "Field cannot contain spaces." << endl;
            return true;
        }
    }
    return false;
}

bool Utils::validateMinLength(const string &input, const int minLength) {
    const int maxLength = 20;

    if (input.length() < size_t(minLength)) {
        cout << "Field is too short. Minimum length is " << minLength << " characters." << endl;
        return false;
    } else if (input.length() > size_t(maxLength)) {
        cout << "Field is too long. Maximum length is " << maxLength << " characters." << endl;
        return false;
    } else {
        return true;
    }
}
