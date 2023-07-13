/*#pragma once
#include <iostream>
#include "string.h"
#include "Gateway.h"
#include "List.h"
using namespace std;

class Table {
public:
	Table(string tableName);
	~Table();
	void loadTable();
	void clearTable();
	bool isEmpty();
	void view();
private:
	string tableName;
	int rows = 0;
	int columns = 0;
	Gateway gateway;
	List<string> *nodes = NULL;
};*/
