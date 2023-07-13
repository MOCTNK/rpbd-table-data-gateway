#include "CashiersGateway.h"

CashiersGateway::CashiersGateway()
{

}

CashiersGateway::~CashiersGateway()
{

}

void CashiersGateway::loadData(map<int, Cashiers*> &mapCashiers, string sql, int id1, int id2) {
    int rows = getCountRows(sql);
    int columns = 4;
    string **data = new string*[columns];
    for(int i = 0; i < columns; i++) {
        data[i] = new string[rows];
    }
    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLRETURN retcode;
    SQLCHAR * ColumnData[columns];
    SQLSMALLINT i,j;

    ColumnData[0] = (SQLCHAR *) malloc (7);
    ColumnData[1] = (SQLCHAR *) malloc (51);
    ColumnData[2] = (SQLCHAR *) malloc (51);
    ColumnData[3] = (SQLCHAR *) malloc (51);
    SQLBindCol(Connection::DB()->statement, 1, SQL_C_CHAR, ColumnData[0], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 2, SQL_C_CHAR, ColumnData[1], 50, nullptr);
    SQLBindCol(Connection::DB()->statement, 3, SQL_C_CHAR, ColumnData[2], 50, nullptr);
    SQLBindCol(Connection::DB()->statement, 4, SQL_C_CHAR, ColumnData[3], 50, nullptr);

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
        Cashiers *cashiers = new Cashiers;
        cashiers->setId(data[0][i]);
        cashiers->setName(data[1][i]);
        cashiers->setSurname(data[2][i]);
        cashiers->setPatronymic(data[3][i]);
        mapCashiers.insert(make_pair(j, cashiers));
    }


    /*for (i = 0; i < columns; i++) {
        if (ColumnData[i]!=NULL) free(ColumnData[i]);
    }*/
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

/*void CashiersGateway::loadFullData(map<int, Cashiers> &mapCashiers) {
    string sql = "SELECT * FROM Cashiers ORDER BY id;";
    loadData(mapCashiers, sql);
}*/

void CashiersGateway::loadRangeData(map<int, Cashiers*> &mapCashiers, int id1, int id2) {
    string sql = "SELECT * FROM cashiers ORDER BY id LIMIT " + to_string(id2 - id1 + 1) + " OFFSET " + to_string(id1 - 1) + ";";
    loadData(mapCashiers, sql, id1, id2);
}

void CashiersGateway::loadDataById(Cashiers *&cashiers, int id) {
    string sql = "SELECT * FROM cashiers WHERE id = " + to_string(id) + ";";
    map<int, Cashiers*> mapCashiers;
    loadData(mapCashiers, sql, id, id);
    cashiers = mapCashiers.at(id);
}

int CashiersGateway::getCountRows(string sql) {
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

int CashiersGateway::getFullCountRows() {
    return getCountRows("SELECT * FROM cashiers;");
}

void CashiersGateway::insert(string name, string surname, string patronymic) {
    string sql = "INSERT INTO cashiers (name, surname, patronymic) VALUES ('"
    + name + "','" + surname + "','" + patronymic + "');";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

void CashiersGateway::update(int id, string column, string data) {
    if(column == "name" || column == "surname" || column == "patronymic") {
        data = "'" + data + "'";
    }
    string sql = "UPDATE cashiers SET " + column + " = " + data + " WHERE id = " + to_string(id) + ";";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

void CashiersGateway::del(int id) {
    string sql = "DELETE FROM cashiers WHERE id = " + to_string(id) + ";";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

