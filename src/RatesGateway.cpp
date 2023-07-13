#include "RatesGateway.h"

RatesGateway::RatesGateway()
{

}

RatesGateway::~RatesGateway()
{

}

void RatesGateway::loadData(map<int, Rates*> &mapRates, Cash<map<int, Currencies*>> &cashCurrencies, string sql, int id1, int id2) {
    int rows = getCountRows(sql);
    int columns = 5;

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
    ColumnData[3] = (SQLCHAR *) malloc (50);
    ColumnData[4] = (SQLCHAR *) malloc (50);
    SQLBindCol(Connection::DB()->statement, 1, SQL_C_CHAR, ColumnData[0], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 2, SQL_C_CHAR, ColumnData[1], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 3, SQL_C_CHAR, ColumnData[2], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 4, SQL_C_CHAR, ColumnData[3], 50, nullptr);
    SQLBindCol(Connection::DB()->statement, 5, SQL_C_CHAR, ColumnData[4], 50, nullptr);

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

    CurrenciesGateway currenciesGateway;
    for(i = 0, j = id1; i < rows; i++, j++) {
        bool check = false;
        Rates *rates = new Rates;
        rates->setId(data[0][i]);
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
        rates->setCurrencySold(currencySold);


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

        currencyPurchased.insert(make_pair(1, currenciesPurchased));
        rates->setCurrencyPurchased(currencyPurchased);
        rates->setSaleRate(data[3][i]);
        rates->setPurchaseRate(data[4][i]);
        mapRates.insert(make_pair(j, rates));
    }
}


void RatesGateway::loadRangeData(map<int, Rates*> &mapRates, Cash<map<int, Currencies*>> &cashCurrencies, int id1, int id2) {
    string sql = "SELECT * FROM rates ORDER BY id LIMIT " + to_string(id2 - id1 + 1) + " OFFSET " + to_string(id1 - 1) + ";";
    loadData(mapRates, cashCurrencies, sql, id1, id2);
}

void RatesGateway::loadDataById(Rates *&rates, Cash<map<int, Currencies*>> &cashCurrencies, int id) {
    string sql = "SELECT * FROM rates WHERE id = " + to_string(id) + ";";
    map<int, Rates*> mapRates;
    loadData(mapRates, cashCurrencies, sql, id, id);
    rates = mapRates.at(id);
}

int RatesGateway::getCountRows(string sql) {
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

int RatesGateway::getFullCountRows() {
    return getCountRows("SELECT * FROM rates;");
}

void RatesGateway::insert(string id_currency_sold,  string id_currency_purchased, string sale_rate, string purchase_rate) {
    string sql = "INSERT INTO rates (id_currency_sold, id_currency_purchased, sale_rate, purchase_rate) VALUES ('"
    + id_currency_sold + "','" + id_currency_purchased + "','" + sale_rate + "','" + purchase_rate + "');";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

void RatesGateway::update(int id, string column, string data) {
    string sql = "UPDATE rates SET " + column + " = " + data + " WHERE id = " + to_string(id) + ";";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

void RatesGateway::del(int id) {
    string sql = "DELETE FROM rates WHERE id = " + to_string(id) + ";";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}


