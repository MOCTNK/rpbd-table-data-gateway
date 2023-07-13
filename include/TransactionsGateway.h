#pragma once
#include <iostream>
#include "string.h"
#include "Gateway.h"
#include "Connection.h"
#include "Transactions.h"
#include "ClientsGateway.h"
#include "CashiersGateway.h"
#include "CurrenciesGateway.h"
#include "RatesGateway.h"
#include "Cash.h"
#include <map>

class TransactionsGateway : public Gateway {
public:
    TransactionsGateway();
    ~TransactionsGateway();
    void loadData(map<int, Transactions*> &mapTransactions, Cash<map<int, Clients*>> &cashClients,
                  Cash<map<int, Cashiers*>> &cashCashiers, Cash<map<int, Currencies*>> &cashCurrencies,
                  Cash<map<int, Rates*>> &cashRates, string sql, int id1, int id2);
    void loadRangeData(map<int, Transactions*> &mapTransactions, Cash<map<int, Clients*>> &cashClients,
                  Cash<map<int, Cashiers*>> &cashCashiers, Cash<map<int, Currencies*>> &cashCurrencies,
                  Cash<map<int, Rates*>> &cashRates, int id1, int id2);
    int getCountRows(string sql);
    int getFullCountRows();
    void insert(string id_currency_sold,  string id_currency_purchased, string id_client,
                string id_cashier, string id_rate_sold, string id_rate_purchased,
                string date_of_transaction, string time_of_transaction,
                string sum_currency_sold, string sum_currency_purchased);
    void update(int id, string column, string data);
    void del(int id);
};
