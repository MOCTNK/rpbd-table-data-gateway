#pragma once
#include <iostream>
#include "string.h"
#include "Gateway.h"
#include "Connection.h"
#include "Currencies.h"
#include "CurrenciesGateway.h"
#include <map>

class CurrenciesGateway : public Gateway {
public:
    CurrenciesGateway();
    ~CurrenciesGateway();
    void loadData(map<int, Currencies*> &mapCurrencies, string sql, int id1, int id2);
    void loadRangeData(map<int, Currencies*> &mapCurrencies, int id1, int id2);
    void loadDataById(Currencies * &currencies, int id);
    int getCountRows(string sql);
    int getFullCountRows();
    void insert(string code, string name);
    void update(int id, string column, string data);
    void del(int id);
};

