#pragma once
#include <iostream>
#include "string.h"
#include "Gateway.h"
#include "Connection.h"
#include "Cashiers.h"
#include <map>

class CashiersGateway : public Gateway {
public:
    CashiersGateway();
    ~CashiersGateway();
    void loadData(map<int, Cashiers*> &mapCashiers, string sql, int id1, int id2);
    void loadRangeData(map<int, Cashiers*> &mapClients, int id1, int id2);
    void loadDataById(Cashiers * &cashiers, int id);
    int getCountRows(string sql);
    int getFullCountRows();
    void insert(string name, string surname, string patronymic);
    void update(int id, string column, string data);
    void del(int id);
};
