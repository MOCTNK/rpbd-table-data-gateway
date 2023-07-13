#include "Menu.h"

Menu::Menu()
{
    //ctor
}

Menu::~Menu()
{
    //dtor
}

void Menu::start() {
    bool exit = false;
    while(!exit) {
        cout << endl;
       cout << "Menu selecting objects:" << endl;
       cout << "1) Clients" << endl;
       cout << "2) Cashiers" << endl;
       cout << "3) Currencies" << endl;
       cout << "4) Rates" << endl;
       cout << "5) Transactions" << endl;
       cout << "6) Exit" << endl;
       cout << "Enter action: " << endl;
       int action = enterNumber(1,6);
       switch (action) {
        case 1:
            cout << endl;
            menuClients();
            break;
        case 2:
            cout << endl;
            menuCashiers();
            break;
        case 3:
            cout << endl;
            menuCurrencies();
            break;
        case 4:
            cout << endl;
            menuRates();
            break;
        case 5:
            cout << endl;
            menuTransactions();
            break;
        case 6:
            cout << endl;
            exit = true;
            break;
       }
    }
}

void Menu::menuClients() {
    userAction.clearCashClients();
    userAction.loadCashClients();
    bool exit = false;
    while(!exit) {
        cout << endl;
       cout << "Menu Clients:" << endl;
       cout << "1) view" << endl;
       cout << "2) insert" << endl;
       cout << "3) update" << endl;
       cout << "4) delete" << endl;
       cout << "5) Exit" << endl;
       cout << "Enter action: " << endl;
       int action = enterNumber(1,5);
       switch (action) {
        case 1:
            cout << endl;
            userAction.viewClients();
            break;
        case 2:
            cout << endl;
            userAction.insertClients();
            break;
        case 3:
            cout << endl;
            userAction.updateClients();
            break;
        case 4:
            cout << endl;
            userAction.deleteClients();
            break;
        case 5:
            cout << endl;
            exit = true;
            break;
       }
    }
}

void Menu::menuCashiers() {
    userAction.clearCashCashiers();
    userAction.loadCashCashiers();
    bool exit = false;
    while(!exit) {
        cout << endl;
       cout << "Menu Cashiers:" << endl;
       cout << "1) view" << endl;
       cout << "2) insert" << endl;
       cout << "3) update" << endl;
       cout << "4) delete" << endl;
       cout << "5) Exit" << endl;
       cout << "Enter action: " << endl;
       int action = enterNumber(1,5);
       switch (action) {
        case 1:
            cout << endl;
            userAction.viewCashiers();
            break;
        case 2:
            cout << endl;
            userAction.insertCashiers();
            break;
        case 3:
            cout << endl;
            userAction.updateCashiers();
            break;
        case 4:
            cout << endl;
            userAction.deleteCashiers();
            break;
        case 5:
            cout << endl;
            exit = true;
            break;
       }
    }
}

void Menu::menuCurrencies() {
    userAction.clearCashCurrencies();
    userAction.loadCashCurrencies();
    bool exit = false;
    while(!exit) {
        cout << endl;
       cout << "Menu Currencies:" << endl;
       cout << "1) view" << endl;
       cout << "2) insert" << endl;
       cout << "3) update" << endl;
       cout << "4) delete" << endl;
       cout << "5) Exit" << endl;
       cout << "Enter action: " << endl;
       int action = enterNumber(1,5);
       switch (action) {
        case 1:
            cout << endl;
            userAction.viewCurrencies();
            break;
        case 2:
            cout << endl;
            userAction.insertCurrencies();
            break;
        case 3:
            cout << endl;
            userAction.updateCurrencies();
            break;
        case 4:
            cout << endl;
            userAction.deleteCurrencies();
            break;
        case 5:
            cout << endl;
            exit = true;
            break;
       }
    }
}

void Menu::menuRates() {
    userAction.clearCashRates();
    userAction.loadCashRates();
    bool exit = false;
    while(!exit) {
        cout << endl;
       cout << "Menu Rates:" << endl;
       cout << "1) view" << endl;
       cout << "2) insert" << endl;
       cout << "3) update" << endl;
       cout << "4) delete" << endl;
       cout << "5) Exit" << endl;
       cout << "Enter action: " << endl;
       int action = enterNumber(1,5);
       switch (action) {
        case 1:
            cout << endl;
            userAction.viewRates();
            break;
        case 2:
            cout << endl;
            userAction.insertRates();
            break;
        case 3:
            cout << endl;
            userAction.updateRates();
            break;
        case 4:
            cout << endl;
            userAction.deleteRates();
            break;
        case 5:
            cout << endl;
            exit = true;
            break;
       }
    }
}

void Menu::menuTransactions() {
    userAction.clearCashTransactions();
    userAction.loadCashTransactions();
    bool exit = false;
    while(!exit) {
       cout << "Menu Transactions:" << endl;
       cout << "1) view" << endl;
       cout << "2) insert" << endl;
       cout << "3) update" << endl;
       cout << "4) delete" << endl;
       cout << "5) Exit" << endl;
       cout << "Enter action: " << endl;
       int action = enterNumber(1,5);
       switch (action) {
        case 1:
            cout << endl;
            userAction.viewTransactions();
            break;
        case 2:
            cout << endl;
            userAction.insertTransactions();
            break;
        case 3:
            cout << endl;
            userAction.updateTransactions();
            break;
        case 4:
            cout << endl;
            userAction.deleteTransactions();
            break;
        case 5:
            cout << endl;
            exit = true;
            break;
       }
    }
}

int Menu::enterNumber(int min, int max) {
	int number = min - 1;
	while (true) {
		cout << ">> ";
		cin >> number;
		if ((number >= min) && (number <= max) && (cin.peek() == '\n')) {
			break;
		}
		else {
			cout << "Incorrect value!" << endl;
			cin.clear();
			while (cin.get() != '\n') {}
		}
	}
	return number;
}

