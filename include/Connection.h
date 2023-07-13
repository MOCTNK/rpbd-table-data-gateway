#pragma once
#include <iostream>
#include "windows.h"
#include <sql.h>
#include <sqlext.h>
#include <string>
using namespace std;

class Connection {
private:
    static Connection *db;
public:
    Connection();
    ~Connection();
    SQLHENV environment = SQL_NULL_HENV;
    SQLHDBC connection = SQL_NULL_HDBC;
    SQLHSTMT statement = SQL_NULL_HSTMT;
    static Connection *DB() {
        if(!db) {
            db = new Connection();
        }
        return db;
    }
    void connect();
    const SQLHSTMT& query(const char* sql);
    void checkTables();
};
