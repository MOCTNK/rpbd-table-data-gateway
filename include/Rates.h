#pragma once
#include <iostream>
#include "string.h"
#include "Object.h"
#include "Currencies.h"
#include <map>
using namespace std;

class Rates : public Object {
public:
    Rates();
    ~Rates();
    void setId(string id);
    void setCurrencySold(map<int, Currencies*> currencySold);
    void setCurrencyPurchased(map<int, Currencies*> currencyPurchased);
    void setSaleRate(string saleRate);
    void setPurchaseRate(string purchaseRate);
    string getId();
    map<int, Currencies*> getCurrencySold();
    map<int, Currencies*> getCurrencyPurchased();
    string getSaleRate();
    string getPurchaseRate();
    Rates& operator=(Rates& other);
private:
    string id;
    map<int, Currencies*> currencySold;
    map<int, Currencies*> currencyPurchased;
    string saleRate;
    string purchaseRate;
    int columns = 5;
};
