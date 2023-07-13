#pragma once
#include <iostream>
#include <iomanip>
#include "string.h"
#include "ClientsGateway.h"
#include "CashiersGateway.h"
#include "CurrenciesGateway.h"
#include "RatesGateway.h"
#include "TransactionsGateway.h"
#include "Clients.h"
#include "Cashiers.h"
#include "Currencies.h"
#include "Rates.h"
#include "Transactions.h"
#include "Cash.h"
#include "math.h"
#include <map>
#include <ctime>
using namespace std;

class UserAction {
public:
    UserAction();
    ~UserAction();
    void viewClients();
    void insertClients();
    void updateClients();
    void deleteClients();
    void clearCashClients();
    void loadCashClients();
    void viewCashiers();
    void insertCashiers();
    void updateCashiers();
    void deleteCashiers();
    void clearCashCashiers();
    void loadCashCashiers();
    void viewCurrencies();
    void insertCurrencies();
    void updateCurrencies();
    void deleteCurrencies();
    void clearCashCurrencies();
    void loadCashCurrencies();
    void viewRates();
    void insertRates();
    void updateRates();
    void deleteRates();
    void clearCashRates();
    void loadCashRates();
    void viewTransactions();
    void insertTransactions();
    void updateTransactions();
    void deleteTransactions();
    void clearCashTransactions();
    void loadCashTransactions();
private:
    Cash<map<int, Clients*>> cashClients;
    Cash<map<int, Cashiers*>> cashCashiers;
    Cash<map<int, Currencies*>> cashCurrencies;
    Cash<map<int, Rates*>> cashRates;
    Cash<map<int, Transactions*>> cashTransactions;
    ClientsGateway clientsGateway;
    CashiersGateway cashiersGateway;
    CurrenciesGateway currenciesGateway;
    RatesGateway ratesGateway;
    TransactionsGateway transactionsGateway;
    int countObjectOnPage = 5;
    int pageClients = 1;
    int pageCashiers = 1;
    int pageCurrencies = 1;
    int pageRates = 1;
    int pageTransactions = 1;
    string enterString();
    int enterNumber(int min, int max);
    bool isOnlyInt(string str);
    bool isOnlyIntAndPoint(string str);
    bool isOnlyString(string str);
    int getRandomInt(int min, int max);
    string getDate();
    string getTime();
    bool isDate(string date);
    bool isTime(string time);
};
