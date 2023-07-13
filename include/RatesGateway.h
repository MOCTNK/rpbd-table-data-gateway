#pragma once
#include <iostream>
#include "string.h"
#include "Gateway.h"
#include "Connection.h"
#include "Rates.h"
#include "CurrenciesGateway.h"
#include "Cash.h"
#include <map>

class RatesGateway : public Gateway {
public:
    RatesGateway();
    ~RatesGateway();
    void loadData(map<int, Rates*> &mapRates, Cash<map<int, Currencies*>> &cashCurrencies, string sql, int id1, int id2);
    void loadRangeData(map<int, Rates*> &mapRates, Cash<map<int, Currencies*>> &cashCurrencies, int id1, int id2);
    void loadDataById(Rates * &rates, Cash<map<int, Currencies*>> &cashCurrencies, int id);
    int getCountRows(string sql);
    int getFullCountRows();
    void insert(string id_currency_sold,  string id_currency_purchased, string sale_rate, string purchase_rate);
    void update(int id, string column, string data);
    void del(int id);
};
