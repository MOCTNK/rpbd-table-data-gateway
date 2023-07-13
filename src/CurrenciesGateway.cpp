#include "CurrenciesGateway.h"

CurrenciesGateway::CurrenciesGateway()
{

}

CurrenciesGateway::~CurrenciesGateway()
{

}

void CurrenciesGateway::loadData(map<int, Currencies*> &mapCurrencies, string sql, int id1, int id2) {
    int rows = getCountRows(sql);
    int columns = 3;
    string **data = new string*[columns];
    for(int i = 0; i < columns; i++) {
        data[i] = new string[rows];
    }
    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLRETURN retcode;
    SQLCHAR * ColumnData[columns];
    SQLSMALLINT i,j;

    ColumnData[0] = (SQLCHAR *) malloc (7);
    ColumnData[1] = (SQLCHAR *) malloc (4);
    ColumnData[2] = (SQLCHAR *) malloc (4);
    SQLBindCol(Connection::DB()->statement, 1, SQL_C_CHAR, ColumnData[0], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 2, SQL_C_CHAR, ColumnData[1], 5, nullptr);
    SQLBindCol(Connection::DB()->statement, 3, SQL_C_CHAR, ColumnData[2], 5, nullptr);

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

    for(i = 0, j = id1; i < rows; i++, j++) {
        Currencies *currencies = new Currencies;
        currencies->setId(data[0][i]);
        currencies->setCode(data[1][i]);
        currencies->setName(data[2][i]);
        mapCurrencies.insert(make_pair(j, currencies));
    }



    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

void CurrenciesGateway::loadRangeData(map<int, Currencies*> &mapCurrencies, int id1, int id2) {
    string sql = "SELECT * FROM currencies ORDER BY id LIMIT " + to_string(id2 - id1 + 1) + " OFFSET " + to_string(id1 - 1) + ";";
    loadData(mapCurrencies, sql, id1, id2);
}

void CurrenciesGateway::loadDataById(Currencies *&currencies, int id) {
    string sql = "SELECT * FROM currencies WHERE id = " + to_string(id) + ";";
    map<int, Currencies*> mapCurrencies;
    loadData(mapCurrencies, sql, id, id);
    currencies = mapCurrencies.at(id);
}

int CurrenciesGateway::getCountRows(string sql) {
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

int CurrenciesGateway::getFullCountRows() {
    return getCountRows("SELECT * FROM currencies;");
}

void CurrenciesGateway::insert(string code, string name) {
    string sql = "INSERT INTO currencies (code, name) VALUES ('"
    + code + "','" + name + "');";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

void CurrenciesGateway::update(int id, string column, string data) {
    if(column == "name" || column == "code") {
        data = "'" + data + "'";
    }
    string sql = "UPDATE currencies SET " + column + " = " + data + " WHERE id = " + to_string(id) + ";";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

void CurrenciesGateway::del(int id) {
    string sql = "DELETE FROM currencies WHERE id = " + to_string(id) + ";";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}
