#include <iostream>
#include "windows.h"
#include <sql.h>
#include <sqlext.h>
#include <string>
#include "Menu.h"
#include "Connection.h"
#include <time.h>
using namespace std;


int main()
{
    srand(time(NULL));
    Connection::DB()->checkTables();
    Menu menu;
    menu.start();
    return 0;
}
