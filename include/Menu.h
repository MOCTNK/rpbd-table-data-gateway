#pragma once
#include <iostream>
#include "string.h"
#include "UserAction.h"
using namespace std;

class Menu {
public:
    Menu();
    ~Menu();
    void start();
    void menuClients();
    void menuCashiers();
    void menuCurrencies();
    void menuRates();
    void menuTransactions();
    int enterNumber(int min, int max);
private:
    UserAction userAction;
};

