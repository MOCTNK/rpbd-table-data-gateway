#pragma once
#include <iostream>
#include "string.h"
#include "Gateway.h"
#include "Connection.h"
#include "Clients.h"
#include <map>

class ClientsGateway : public Gateway {
public:
    ClientsGateway();
    ~ClientsGateway();
    void loadData(map<int, Clients*> &mapClients, string sql, int id1, int id2);
    void loadRangeData(map<int, Clients*> &mapClients, int id1, int id2);
    void loadDataById(Clients * &clients, int id);
    int getCountRows(string sql);
    int getFullCountRows();
    void insert(string name, string surname, string patronymic, string passportSeries, string passportNumber);
    void update(int id, string column, string data);
    void del(int id);
};

