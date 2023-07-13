#include "ClientsGateway.h"

ClientsGateway::ClientsGateway()
{

}

ClientsGateway::~ClientsGateway()
{

}

void ClientsGateway::loadData(map<int, Clients*> &mapClients, string sql, int id1, int id2) {
    int rows = getCountRows(sql);
    int columns = 6;
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
    ColumnData[4] = (SQLCHAR *) malloc (5);
    ColumnData[5] = (SQLCHAR *) malloc (7);
    SQLBindCol(Connection::DB()->statement, 1, SQL_C_CHAR, ColumnData[0], 7, nullptr);
    SQLBindCol(Connection::DB()->statement, 2, SQL_C_CHAR, ColumnData[1], 50, nullptr);
    SQLBindCol(Connection::DB()->statement, 3, SQL_C_CHAR, ColumnData[2], 50, nullptr);
    SQLBindCol(Connection::DB()->statement, 4, SQL_C_CHAR, ColumnData[3], 50, nullptr);
    SQLBindCol(Connection::DB()->statement, 5, SQL_C_CHAR, ColumnData[4], 5, nullptr);
    SQLBindCol(Connection::DB()->statement, 6, SQL_C_CHAR, ColumnData[5], 7, nullptr);

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
        Clients *clients = new Clients;
        clients->setId(data[0][i]);
        clients->setName(data[1][i]);
        clients->setSurname(data[2][i]);
        clients->setPatronymic(data[3][i]);
        clients->setPassportSeries(data[4][i]);
        clients->setPassportNumber(data[5][i]);
        mapClients.insert(make_pair(j, clients));
    }


    /*for (i = 0; i < columns; i++) {
        if (ColumnData[i]!=NULL) free(ColumnData[i]);
    }*/
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

/*void ClientsGateway::loadFullData(map<int, Clients> &mapClients) {
    string sql = "SELECT * FROM clients ORDER BY id;";
    loadData(mapClients, sql);
}*/

void ClientsGateway::loadRangeData(map<int, Clients*> &mapClients, int id1, int id2) {
    string sql = "SELECT * FROM clients ORDER BY id LIMIT " + to_string(id2 - id1 + 1) + " OFFSET " + to_string(id1 - 1) + ";";
    loadData(mapClients, sql, id1, id2);
}

void ClientsGateway::loadDataById(Clients *&clients, int id) {
    string sql = "SELECT * FROM clients WHERE id = " + to_string(id) + ";";
    map<int, Clients*> mapClients;
    loadData(mapClients, sql, id, id);
    clients = mapClients.at(id);
}

int ClientsGateway::getCountRows(string sql) {
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

int ClientsGateway::getFullCountRows() {
    return getCountRows("SELECT * FROM clients;");
}

void ClientsGateway::insert(string name, string surname, string patronymic, string passportSeries, string passportNumber) {
    string sql = "INSERT INTO clients (name, surname, patronymic, passport_series, passport_number) VALUES ('"
    + name + "','" + surname + "','" + patronymic + "'," + passportSeries + "," + passportNumber + ");";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

void ClientsGateway::update(int id, string column, string data) {
    if(column == "name" || column == "surname" || column == "patronymic") {
        data = "'" + data + "'";
    }
    string sql = "UPDATE clients SET " + column + " = " + data + " WHERE id = " + to_string(id) + ";";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

void ClientsGateway::del(int id) {
    string sql = "DELETE FROM clients WHERE id = " + to_string(id) + ";";

    Connection::DB()->statement = Connection::DB()->query(sql.c_str());
    SQLFreeStmt(Connection::DB()->statement, SQL_CLOSE);
}

