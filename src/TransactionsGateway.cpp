#include "TransactionsGateway.h"

TransactionsGateway::TransactionsGateway()
{

}

TransactionsGateway::~TransactionsGateway()
{

}

void TransactionsGateway::loadData(map<int, Transactions*> &mapTransactions, Cash<map<int, Clients*>> &cashClients,
                  Cash<map<int, Cashiers*>> &cashCashiers, Cash<map<int, Currencies*>> &cashCurrencies,
                  Cash<map<int, Rates*>> &cashRates, string sql, int id1, int id2) {
    int rows = getCountRows(sql);
    int columns = 11;

    string **data = new string*[columns];
    for(int i = 0; i < columns; i++) {
        data[i] = new string[rows];
    }
    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLRETURN retcode;
    SQLCHAR * ColumnData[columns];
    SQLSMALLINT i,j;

    ColumnData[0] = (SQLCHAR *) malloc (7);
    ColumnData[1] = (SQLCHAR *) malloc (7);
    ColumnData[2] = (SQLCHAR *) malloc (7);
    ColumnData[3] = (SQLCHAR *) malloc (7);
    ColumnData[4] = (SQLCHAR *) malloc (7);
    ColumnData[5] = (SQLCHAR *) malloc (7);
    ColumnData[6] = (SQLCHAR *) malloc (7);
    ColumnData[7] = (SQLCHAR *) malloc (50);
    ColumnData[8] = (SQLCHAR *) malloc (50);
    ColumnData[9] = (SQLCHAR *) malloc (50);
    ColumnData[10] = (SQLCHAR *) malloc (50);
    SQLBindCol(Connection::DB()->statement, 1, SQL_C_CHAR, ColumnData[0], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 2, SQL_C_CHAR, ColumnData[1], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 3, SQL_C_CHAR, ColumnData[2], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 4, SQL_C_CHAR, ColumnData[3], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 5, SQL_C_CHAR, ColumnData[4], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 6, SQL_C_CHAR, ColumnData[5], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 7, SQL_C_CHAR, ColumnData[6], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 8, SQL_C_CHAR, ColumnData[7], 50, nullptr);
    SQLBindCol(Connection::DB()->statement, 9, SQL_C_CHAR, ColumnData[8], 50, nullptr);
    SQLBindCol(Connection::DB()->statement, 10, SQL_C_CHAR, ColumnData[9], 50, nullptr);
    SQLBindCol(Connection::DB()->statement, 11, SQL_C_CHAR, ColumnData[10], 50, nullptr);

    retcode = SQLExecute(Connection::DB()->statement);
    for (i=0; ; i++) {
        retcode = SQLFetch(Connection::DB()->statement);

        if (retcode == SQL_NO_DATA) {
            break;
        }

        for (j=0; j<columns; j++) {
            string temp((const char*)ColumnData[j]);
            data[j][i] = temp;
        }

    }

    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);

    ClientsGateway clientsGateway;
    CashiersGateway cashiersGateway;
    CurrenciesGateway currenciesGateway;
    RatesGateway ratesGateway;
    for(i = 0, j = id1; i < rows; i++, j++) {
        bool check = false;
        Transactions *transactions = new Transactions;
        transactions->setId(data[0][i]);
        Currencies *currenciesSold;
        map<int, Currencies*> currencySold;
        for(int k = 0; k < cashCurrencies.getSize(); k++) {
            map<int, Currencies*> tempMap = cashCurrencies.getElementDataById(k);
            for (map<int, Currencies*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                if(stoi(it->second->getId()) == stoi(data[1][i])) {
                    currenciesSold = cashCurrencies.getElementDataById(k).at(it->first);
                    check = true;
                    break;
                }
            }
        }

        if(!check) {
            currenciesSold = new Currencies();
            currenciesGateway.loadDataById(currenciesSold, stoi(data[1][i]));
        }
        check = false;
        currencySold.insert(make_pair(1, currenciesSold));
        transactions->setCurrencySold(currencySold);


        Currencies *currenciesPurchased;
        map<int, Currencies*> currencyPurchased;
        for(int k = 0; k < cashCurrencies.getSize(); k++) {
            map<int, Currencies*> tempMap = cashCurrencies.getElementDataById(k);
            for (map<int, Currencies*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                if(stoi(it->second->getId()) == stoi(data[2][i])) {
                    currenciesPurchased = cashCurrencies.getElementDataById(k).at(it->first);
                    check = true;
                    break;
                }
            }
        }

        if(!check) {
            currenciesPurchased = new Currencies();
            currenciesGateway.loadDataById(currenciesPurchased, stoi(data[2][i]));
        }

        check = false;
        currencyPurchased.insert(make_pair(1, currenciesPurchased));
        transactions->setCurrencyPurchased(currencyPurchased);

        Clients *clients;
        map<int, Clients*> clientsMap;
        for(int k = 0; k < cashClients.getSize(); k++) {
            map<int, Clients*> tempMap = cashClients.getElementDataById(k);
            for (map<int, Clients*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                if(stoi(it->second->getId()) == stoi(data[3][i])) {
                    clients = cashClients.getElementDataById(k).at(it->first);
                    check = true;
                    break;
                }
            }
        }

        if(!check) {
            clients = new Clients();
            clientsGateway.loadDataById(clients, stoi(data[3][i]));
        }

        check = false;
        clientsMap.insert(make_pair(1, clients));
        transactions->setClient(clientsMap);

        Cashiers *cashiers;
        map<int, Cashiers*> cashiersMap;
        for(int k = 0; k < cashCashiers.getSize(); k++) {
            map<int, Cashiers*> tempMap = cashCashiers.getElementDataById(k);
            for (map<int, Cashiers*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                if(stoi(it->second->getId()) == stoi(data[4][i])) {
                    cashiers = cashCashiers.getElementDataById(k).at(it->first);
                    check = true;
                    break;
                }
            }
        }

        if(!check) {
            cashiers = new Cashiers();
            cashiersGateway.loadDataById(cashiers, stoi(data[4][i]));
        }

        check = false;
        cashiersMap.insert(make_pair(1, cashiers));
        transactions->setCashier(cashiersMap);

        Rates *rateSold;
        map<int, Rates*> ratesMap;
        for(int k = 0; k < cashRates.getSize(); k++) {
            map<int, Rates*> tempMap = cashRates.getElementDataById(k);
            for (map<int, Rates*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                if(stoi(it->second->getId()) == stoi(data[5][i])) {
                    rateSold = cashRates.getElementDataById(k).at(it->first);
                    check = true;
                    break;
                }
            }
        }

        if(!check) {
            rateSold = new Rates();
            ratesGateway.loadDataById(rateSold, cashCurrencies, stoi(data[5][i]));
        }

        check = false;
        ratesMap.insert(make_pair(1, rateSold));
        transactions->setRateSold(ratesMap);

        Rates *ratePurchased;
        map<int, Rates*> rates2Map;
        for(int k = 0; k < cashRates.getSize(); k++) {
            map<int, Rates*> tempMap = cashRates.getElementDataById(k);
            for (map<int, Rates*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                if(stoi(it->second->getId()) == stoi(data[6][i])) {
                    ratePurchased = cashRates.getElementDataById(k).at(it->first);
                    check = true;
                    break;
                }
            }
        }

        if(!check) {
            ratePurchased = new Rates();
            ratesGateway.loadDataById(ratePurchased, cashCurrencies, stoi(data[6][i]));
        }

        check = false;
        rates2Map.insert(make_pair(1, ratePurchased));
        transactions->setRatePurchased(rates2Map);

        transactions->setDate(data[7][i]);
        transactions->setTime(data[8][i]);
        transactions->setSumCurrencySold(data[9][i]);
        transactions->setSumCurrencyPurchased(data[10][i]);
        mapTransactions.insert(make_pair(j, transactions));
    }
}


void TransactionsGateway::loadRangeData(map<int, Transactions*> &mapTransactions, Cash<map<int, Clients*>> &cashClients,
                  Cash<map<int, Cashiers*>> &cashCashiers, Cash<map<int, Currencies*>> &cashCurrencies,
                  Cash<map<int, Rates*>> &cashRates, int id1, int id2) {
    string sql = "SELECT * FROM transactions ORDER BY id LIMIT " + to_string(id2 - id1 + 1) + " OFFSET " + to_string(id1 - 1) + ";";
    loadData(mapTransactions, cashClients, cashCashiers, cashCurrencies, cashRates, sql, id1, id2);
}

int TransactionsGateway::getCountRows(string sql) {
    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLRETURN retcode;
    int rows = 0;
    retcode = SQLExecute(Connection::DB()->statement);
    for (;;) {
        retcode = SQLFetch(Connection::DB()->statement);

        if (retcode == SQL_NO_DATA) {
            break;
        }
        rows++;
    }
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
    return rows;
}

int TransactionsGateway::getFullCountRows() {
    return getCountRows("SELECT * FROM transactions;");
}

void TransactionsGateway::insert(string id_currency_sold,  string id_currency_purchased, string id_client,
                string id_cashier, string id_rate_sold, string id_rate_purchased,
                string date_of_transaction, string time_of_transaction,
                string sum_currency_sold, string sum_currency_purchased) {
    string sql = "INSERT INTO transactions (id_currency_sold, id_currency_purchased, id_client, id_cashier, id_rate_sold, id_rate_purchased, date_of_transaction, time_of_transaction, sum_currency_sold, sum_currency_purchased) VALUES ('"
    + id_currency_sold + "','" + id_currency_purchased + "','" + id_client + "','" + id_cashier + "','" + id_rate_sold
    + "','" + id_rate_purchased + "','" + date_of_transaction + "','"
    + time_of_transaction + "','" + sum_currency_sold + "','" + sum_currency_purchased + "');";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

void TransactionsGateway::update(int id, string column, string data) {
    if(column == "date_of_transaction" || column == "time_of_transaction") {
        data = "'" + data + "'";
    }
    string sql = "UPDATE transactions SET " + column + " = " + data + " WHERE id = " + to_string(id) + ";";
    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

void TransactionsGateway::del(int id) {
    string sql = "DELETE FROM transactions WHERE id = " + to_string(id) + ";";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}


