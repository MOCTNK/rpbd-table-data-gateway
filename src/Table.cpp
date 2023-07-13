#include "Table.h"

/*Table::Table(string tableName) {
	this->tableName = tableName;
	this->gateway.set(tableName);
	loadTable();
}

Table::~Table() {
    clearTable();
}

void Table::loadTable() {
    this->nodes = this->gateway.getTable();
    this->rows = stoi(nodes[0].getDataById(nodes[0].getSize())) - 1;
    this->columns = nodes[0].getSize() - 1;
}

void Table::clearTable() {
    if(!isEmpty()) {
        rows = 0;
        columns = 0;
        delete [] nodes;
    }

}

bool Table::isEmpty() {
    if(rows <= 0) {
        return true;
    } else {
        return false;
    }
}

void Table::view() {
    cout << "name: " << tableName;
    cout << "   columns: " << columns;
    cout << "   rows: " << rows << endl;
    for(int i = 0; i < rows+1; i++) {
        for(int j = 0; j < columns; j++) {
            string str = nodes[i].getDataById(j+1)+"\t\t";
            printf(str.c_str());
        }
        printf("\n");
    }
}*/
