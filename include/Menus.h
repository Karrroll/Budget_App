#ifndef MENUS_H
#define MENUS_H

#include <iostream>

#include "Type.h"

using namespace std;

class Menus {
public:
    static void showMainMenu();
    static void showUserMenu();
    static void showDateSelectionMenu();
    static void showMenu(MenuType menuType);
};

#endif // MENUS_H
