#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

enum class FieldType {
    FIRST_NAME,
    LAST_NAME,
    LOGIN,
    PASSWORD
};

enum class TransactionType {
    INCOME,
    EXPENSE
};

enum class MenuType {
    MAIN_MENU,
    USER_MENU,
    DATE_SELECTION_MENU
};

enum class BalanceType {
    CURRENT_MONTH,
    PREVIOUS_MONTH,
    CUSTOM_PERIOD
};

#endif // TYPE_H_INCLUDED
