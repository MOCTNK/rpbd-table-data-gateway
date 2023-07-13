#pragma once
#include <iostream>
#include "string.h"
#include "Object.h"
#include "Currencies.h"
#include "Clients.h"
#include "Cashiers.h"
#include "Rates.h"
#include <map>
using namespace std;

class Transactions : public Object {
public:
    Transactions();
    ~Transactions();
    void setId(string id);
    void setCurrencySold(map<int, Currencies*> currencySold);
    void setCurrencyPurchased(map<int, Currencies*> currencyPurchased);
    void setClient(map<int, Clients*> client);
    void setCashier(map<int, Cashiers*> cashier);
    void setRateSold(map<int, Rates*> rateSold);
    void setRatePurchased(map<int, Rates*> ratePurchased);
    void setDate(string date);
    void setTime(string time);
    void setSumCurrencySold(string sumCurrencySold);
    void setSumCurrencyPurchased(string sumCurrencyPurchased);
    string getId();
    map<int, Currencies*> getCurrencySold();
    map<int, Currencies*> getCurrencyPurchased();
    map<int, Clients*> getClient();
    map<int, Cashiers*> getCashier();
    map<int, Rates*> getRateSold();
    map<int, Rates*> getRatePurchased();
    string getDate();
    string getTime();
    string getSumCurrencySold();
    string getSumCurrencyPurchased();
    Transactions& operator=(Transactions& other);
private:
    string id;
    map<int, Currencies*> currencySold;
    map<int, Currencies*> currencyPurchased;
    map<int, Clients*> client;
    map<int, Cashiers*> cashier;
    map<int, Rates*> rateSold;
    map<int, Rates*> ratePurchased;
    string date;
    string time;
    string sumCurrencySold;
    string sumCurrencyPurchased;
    int columns = 11;
};
