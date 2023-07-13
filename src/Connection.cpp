#include "Connection.h"
Connection *Connection::db = 0;

void Connection::connect() {
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &environment) == SQL_ERROR)
	{
		fwprintf(stderr, L"Unable to allocate an environment handle\n");
		exit(-1);
	}

	if (SQLSetEnvAttr(environment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0) == SQL_ERROR) {
		fwprintf(stderr, L"Unable to set an environment variable\n");
		exit(-1);
	}

	if (SQLAllocHandle(SQL_HANDLE_DBC, environment, &connection) == SQL_ERROR) {
		fwprintf(stderr, L"Unable to allocate an connection handle\n");
		exit(-1);
	}

	if (SQLConnect(connection, (SQLCHAR*)"PostgreSQL35W", SQL_NTS, (SQLCHAR*)"student", SQL_NTS, (SQLCHAR*)"123", SQL_NTS) == SQL_ERROR) {
		fwprintf(stderr, L"Unable to connect\n");
		exit(-1);
	}

	if (SQLAllocHandle(SQL_HANDLE_STMT, connection, &statement) == SQL_ERROR) {
		fwprintf(stderr, L"Unable to allocate stmt handle\n");
		exit(-1);
	}
}

Connection::Connection() {
	connect();
}

Connection::~Connection()
{
	if (this->statement != SQL_NULL_HSTMT)
		SQLFreeHandle(SQL_HANDLE_STMT, this->statement);

	if (this->connection != SQL_NULL_HDBC) {
		SQLDisconnect(this->connection);
		SQLFreeHandle(SQL_HANDLE_DBC, this->connection);
	}

	if (this->environment != SQL_NULL_HENV) {
        SQLFreeHandle(SQL_HANDLE_ENV, this->environment);
	}
    delete db;
}

const SQLHSTMT& Connection::query(const char* sql)
{
	SQLRETURN ret = SQLExecDirect(statement, (SQLCHAR*)sql, SQL_NTS);
	if (ret == SQL_SUCCESS) {
		return this->statement;
	}
	return nullptr;
}

void Connection::checkTables()
{
    string sql;
	sql = "CREATE TABLE IF not exists clients (id SERIAL PRIMARY KEY,name VARCHAR(50) NOT NULL,surname VARCHAR(50) NOT NULL,patronymic VARCHAR(50) NOT NULL,passport_series VARCHAR(4) NOT NULL,passport_number VARCHAR(6) NOT NULL);";
    query(sql.c_str());

    sql = "CREATE TABLE IF not exists cashiers (id SERIAL PRIMARY KEY, name VARCHAR(50) NOT NULL, surname VARCHAR(50) NOT NULL, patronymic VARCHAR(50) NOT NULL);";
    query(sql.c_str());

    sql = "CREATE TABLE IF not exists currencies (id SERIAL PRIMARY KEY, code VARCHAR(3) NOT NULL, name VARCHAR(3) NOT NULL);";
    query(sql.c_str());

    sql = "CREATE TABLE IF not exists rates (id SERIAL PRIMARY KEY,id_currency_sold INTEGER NOT NULL,id_currency_purchased INTEGER NOT NULL,sale_rate DECIMAL NOT NULL,purchase_rate DECIMAL NOT NULL,FOREIGN KEY (id_currency_sold) REFERENCES currencies(id),FOREIGN KEY (id_currency_purchased) REFERENCES currencies(id));";
    query(sql.c_str());

    sql = "CREATE TABLE IF not exists transactions (id SERIAL PRIMARY KEY, id_currency_sold INTEGER NOT NULL, id_currency_purchased INTEGER NOT NULL, id_client INTEGER NOT NULL, id_cashier INTEGER NOT NULL, id_rate_sold INTEGER NOT NULL, id_rate_purchased INTEGER NOT NULL, date_of_transaction DATE NOT NULL, time_of_transaction TIME NOT NULL, sum_currency_sold DECIMAL DEFAULT 0, sum_currency_purchased DECIMAL DEFAULT 0, FOREIGN KEY (id_currency_sold) REFERENCES currencies(id), FOREIGN KEY (id_currency_purchased) REFERENCES currencies(id), FOREIGN KEY (id_client) REFERENCES clients(id), FOREIGN KEY (id_cashier) REFERENCES cashiers(id), FOREIGN KEY (id_rate_sold) REFERENCES rates(id), FOREIGN KEY (id_rate_purchased) REFERENCES rates(id));";
    query(sql.c_str());
}
