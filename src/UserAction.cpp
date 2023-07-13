#include "UserAction.h"

UserAction::UserAction()
{
}

UserAction::~UserAction()
{
    //dtor
}

void UserAction::viewClients() {
    if(cashClients.getNow().empty()) {
        cout << "Object is empty!" << endl;
    } else {
        bool exit = false;
        int id1 = 1 + (pageClients - 1) * countObjectOnPage;
        int id2 = countObjectOnPage + (pageClients - 1) * countObjectOnPage;
        int rows = clientsGateway.getFullCountRows();
        while(!exit) {
            cout << setfill('-') << right << "+" << setw(4) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << endl;
            cout << setfill(' ') << left << "| " << setw(2) << "N" << "| " << setw(18) << "name"
            << "| " << setw(18) << "surname" << "| " << setw(18) << "patronymic"
            << "| " << setw(18) << "passport_series" << "| " << setw(18) << "passport_number" << "| " << endl;
            cout << setfill('-') << right << "+" << setw(4) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << endl;
            for(int i = id1, j = 0; j <  cashClients.getNow().size(); i++, j++) {
                cout << setfill(' ') << left
                << "| " << setw(2) << i
                << "| " << setw(18) << cashClients.getNow().at(i)->getName()
                << "| " << setw(18) << cashClients.getNow().at(i)->getSurname()
                << "| " << setw(18) << cashClients.getNow().at(i)->getPatronymic()
                << "| " << setw(18) << cashClients.getNow().at(i)->getPassportSeries()
                << "| " << setw(18) << cashClients.getNow().at(i)->getPassportNumber() << "| " << endl;
                cout << setfill('-') << right << "+" << setw(4) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << endl;
            }
            int maxPage = rows % countObjectOnPage == 0 ? rows / countObjectOnPage : rows / countObjectOnPage + 1;
            cout << "pages: " << pageClients << "/" << maxPage << endl;
            cout << "1) next" << endl;
            cout << "2) prev" << endl;
            cout << "3) Exit" << endl;
            cout << "Enter action: " << endl;
            int action = enterNumber(1,3);
            switch (action) {
            case 1: {
                if(pageClients < maxPage) {
                    id1 += countObjectOnPage;
                    id2 += countObjectOnPage;
                    if(cashClients.isNextNull()) {
                        map<int, Clients*> mapClients;
                        clientsGateway.loadRangeData(mapClients, id1, id2);
                        cashClients.addToEnd(mapClients);
                    } else {
                        cashClients.Next();
                    }
                    pageClients++;
                }
                break;
            }
            case 2: {
                if(pageClients > 1) {
                    id1 -= countObjectOnPage;
                    id2 -= countObjectOnPage;
                    if(cashClients.isPrevNull()) {
                        map<int, Clients*> mapClients;
                        clientsGateway.loadRangeData(mapClients, id1, id2);
                        cashClients.addToBegin(mapClients);
                    } else {
                        cashClients.Prev();
                    }
                    pageClients--;
                }
                break;
            }
            case 3: {
                exit = true;
                break;
            }
            default:
                cout << "Incorrect value!" << endl;
                break;
            }
        }
    }
}

void UserAction::insertClients() {
    int rows = clientsGateway.getFullCountRows();
    string name;
    while(true) {
        cout << "Enter name: " << endl;
        name = enterString();
        if(name.size() > 0 && name.size() <= 50 && isOnlyString(name)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    string surname;
    while(true) {
        cout << "Enter surname: " << endl;
        surname = enterString();
        if(surname.size() > 0 && surname.size() <= 50 && isOnlyString(surname)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string patronymic;
    while(true) {
        cout << "Enter patronymic: " << endl;
        patronymic = enterString();
        if(patronymic.size() > 0 && patronymic.size() <= 50 && isOnlyString(patronymic)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    string passportSeries;
    while(true) {
        cout << "Enter passport series: " << endl;
        passportSeries = enterString();
        if(passportSeries.size() == 4 && isOnlyInt(passportSeries)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    string passportNumber;
    while(true) {
        cout << "Enter passport number: " << endl;
        passportNumber = enterString();
        if(passportNumber.size() == 6 && isOnlyInt(passportNumber)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    map<int, Clients*> tempMap;
    tempMap = cashClients.getElementDataById(cashClients.getSize() - 1);
    int id = getRandomInt(100, 10000);
    if (tempMap.find(rows) != tempMap.end()) {
        if(tempMap.size() < countObjectOnPage) {
            Clients *tempClient = new Clients;
            tempClient->setId(to_string(rows+1));
            tempClient->setName(name);
            tempClient->setSurname(surname);
            tempClient->setPatronymic(patronymic);
            tempClient->setPassportSeries(passportSeries);
            tempClient->setPassportNumber(passportNumber);
            tempMap.insert(make_pair(rows+1, tempClient));
            cashClients.setElementDataById(cashClients.getSize() - 1, tempMap);
        }
    }
    clientsGateway.insert(name, surname, patronymic, passportSeries, passportNumber);
    cout << "Node inserted!" << endl;
}

void UserAction::updateClients() {
    bool exit = false;
    string id;
    map<int, Clients*> tempMap;
    int rows = clientsGateway.getFullCountRows();
    while(true) {
        cout << "Enter N nodes: " << endl;
        id = enterString();
        if(isOnlyInt(id) && stoi(id) <= rows) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    string column;
    while(true) {
        cout << "1)name" << endl;
        cout << "2)surname" << endl;
        cout << "3)patronymic" << endl;
        cout << "4)passport_series" << endl;
        cout << "5)passport_number" << endl;
        cout << "Enter column: " << endl;
        column = enterString();
        if(stoi(column) >= 1 && stoi(column) <= 5 && isOnlyInt(column)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    int columnInt = stoi(column);
    string columnName;
    switch(columnInt) {
    case 1:
        columnName = "name";
        break;
    case 2:
        columnName = "surname";
        break;
    case 3:
        columnName = "patronymic";
        break;
    case 4:
        columnName = "passport_series";
        break;
    case 5:
        columnName = "passport_number";
        break;
    }

    string data;
    while(true) {
        cout << "Enter data: " << endl;
        data = enterString();

        if(stoi(column) >= 1 && stoi(column) <= 3 && isOnlyString(data) && data.size() > 0 && data.size() <= 50) {
            break;
        }
        if(stoi(column) == 4 && isOnlyInt(data) && data.size() == 4) {
            break;
        }
        if(stoi(column) == 5 && isOnlyInt(data) && data.size() == 6) {
            break;
        }
        cout << "Incorrect value!" << endl;
    }
    bool checkCash = false;
    for(int i = 0; i < cashClients.getSize(); i++) {
        tempMap = cashClients.getElementDataById(i);
        if (tempMap.find(stoi(id)) != tempMap.end()) {
            checkCash = true;
            Clients *tempClient = tempMap.at(stoi(id));
            switch(columnInt) {
            case 1:
                tempClient->setName(data);
                break;
            case 2:
                tempClient->setSurname(data);
                break;
            case 3:
                tempClient->setPatronymic(data);
                break;
            case 4:
                tempClient->setPassportSeries(data);
                break;
            case 5:
                tempClient->setPassportNumber(data);
                break;
            }
            tempMap[stoi(id)] = tempClient;
            cashClients.setElementDataById(i, tempMap);
            break;
        }
    }
    if(!checkCash) {
        clientsGateway.loadRangeData(tempMap, stoi(id), stoi(id));
    }
    clientsGateway.update(stoi(tempMap.at(stoi(id))->getId()), columnName, data);
    cout << "Node updated!" << endl;
}

void UserAction::deleteClients() {
    int rows = clientsGateway.getFullCountRows();
    string id;
    while(true) {
        cout << "Enter N nodes: " << endl;
        id = enterString();
        if(isOnlyInt(id) && stoi(id) <= rows) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    map<int, Clients*> tempMap;
    int idDel;
    bool checkCash = false;
    for(int i = 0; i < cashClients.getSize(); i++) {
        tempMap = cashClients.getElementDataById(i);
        if (tempMap.find(stoi(id)) != tempMap.end()) {
            checkCash = true;
            idDel = i;
            break;
        }
    }
    if(!checkCash) {
        idDel = 0;
        clientsGateway.loadRangeData(tempMap, stoi(id), stoi(id));
    }

    int tempId;
        for(int i = idDel, tempId = stoi(id); i < cashClients.getSize();) {
            map<int, Clients*> tempMap1;
            tempMap1 = cashClients.getElementDataById(i);
            if (!(tempMap1.find(tempId) != tempMap1.end())) {
                tempId++;
                continue;
            }
            for(int j = 0; j < tempMap1.size(); j++) {
                if (!(tempMap1.find(tempId+1) != tempMap1.end())) {
                    break;
                }
                tempMap1[tempId] = tempMap1[tempId+1];
                tempId++;
            }

            if(i+1 != cashClients.getSize()) {
                map<int, Clients*> tempMap2;
                tempMap2 = cashClients.getElementDataById(i+1);
                tempMap1[tempId] = tempMap2[tempId+1];
                tempId++;
            } else {
                if (tempMap1.find(rows) != tempMap1.end()) {
                    tempMap1.erase(tempId);
                } else {
                    map<int, Clients*> tempMap2;
                    clientsGateway.loadRangeData(tempMap2, tempId+1, tempId+1);
                    tempMap1[tempId] = tempMap2[tempId+1];
                }
            }
            if(tempMap1.empty()) {
                cashClients.Prev();
                cashClients.delToEnd();
                pageClients--;
            } else {
                cashClients.setElementDataById(i, tempMap1);
            }
            i++;
        }
    clientsGateway.del(stoi(tempMap.at(stoi(id))->getId()));
    cout << "Node deleted!" << endl;
}

void UserAction::clearCashClients() {
    pageClients = 1;
    cashClients.clear();
}

void UserAction::loadCashClients() {
    pageClients = 1;
    map<int, Clients*> mapClients;
    clientsGateway.loadRangeData(mapClients, 1, countObjectOnPage);
    cashClients.addToEnd(mapClients);
}

void UserAction::viewCashiers() {
    if(cashCashiers.getNow().empty()) {
        cout << "Object is empty!" << endl;
    } else {
        bool exit = false;
        int id1 = 1 + (pageCashiers - 1) * countObjectOnPage;
        int id2 = countObjectOnPage + (pageCashiers - 1) * countObjectOnPage;
        int rows = cashiersGateway.getFullCountRows();
        while(!exit) {
            cout << setfill('-') << right << "+" << setw(4) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << endl;
            cout << setfill(' ') << left << "| " << setw(2) << "N" << "| " << setw(18) << "name"
            << "| " << setw(18) << "surname" << "| " << setw(18) << "patronymic" << "| " << endl;
            cout << setfill('-') << right << "+" << setw(4) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << endl;
            for(int i = id1, j = 0; j <  cashCashiers.getNow().size(); i++, j++) {
                cout << setfill(' ') << left
                << "| " << setw(2) << i
                << "| " << setw(18) << cashCashiers.getNow().at(i)->getName()
                << "| " << setw(18) << cashCashiers.getNow().at(i)->getSurname()
                << "| " << setw(18) << cashCashiers.getNow().at(i)->getPatronymic() << "| " << endl;
                cout << setfill('-') << right << "+" << setw(4) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << endl;
            }
            int maxPage = rows % countObjectOnPage == 0 ? rows / countObjectOnPage : rows / countObjectOnPage + 1;
            cout << "pages: " << pageCashiers << "/" << maxPage << endl;
            cout << "1) next" << endl;
            cout << "2) prev" << endl;
            cout << "3) Exit" << endl;
            cout << "Enter action: " << endl;
            int action = enterNumber(1,3);
            switch (action) {
            case 1: {
                if(pageCashiers < maxPage) {
                    id1 += countObjectOnPage;
                    id2 += countObjectOnPage;
                    if(cashCashiers.isNextNull()) {
                        map<int, Cashiers*> mapCashiers;
                        cashiersGateway.loadRangeData(mapCashiers, id1, id2);
                        cashCashiers.addToEnd(mapCashiers);
                    } else {
                        cashCashiers.Next();
                    }
                    pageCashiers++;
                }
                break;
            }
            case 2: {
                if(pageCashiers > 1) {
                    id1 -= countObjectOnPage;
                    id2 -= countObjectOnPage;
                    if(cashCashiers.isPrevNull()) {
                        map<int, Cashiers*> mapCashiers;
                        cashiersGateway.loadRangeData(mapCashiers, id1, id2);
                        cashCashiers.addToBegin(mapCashiers);
                    } else {
                        cashCashiers.Prev();
                    }
                    pageCashiers--;
                }
                break;
            }
            case 3: {
                exit = true;
                break;
            }
            default:
                cout << "Incorrect value!" << endl;
                break;
            }
        }
    }
}

void UserAction::insertCashiers() {
    int rows = cashiersGateway.getFullCountRows();
    string name;
    while(true) {
        cout << "Enter name: " << endl;
        name = enterString();
        if(name.size() > 0 && name.size() <= 50 && isOnlyString(name)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    string surname;
    while(true) {
        cout << "Enter surname: " << endl;
        surname = enterString();
        if(surname.size() > 0 && surname.size() <= 50 && isOnlyString(surname)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string patronymic;
    while(true) {
        cout << "Enter patronymic: " << endl;
        patronymic = enterString();
        if(patronymic.size() > 0 && patronymic.size() <= 50 && isOnlyString(patronymic)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    map<int, Cashiers*> tempMap;
    tempMap = cashCashiers.getElementDataById(cashCashiers.getSize() - 1);
    int id = getRandomInt(100, 10000);
    if (tempMap.find(rows) != tempMap.end()) {
        if(tempMap.size() < countObjectOnPage) {
            Cashiers *tempCashier = new Cashiers;
            tempCashier->setId(to_string(rows+1));
            tempCashier->setName(name);
            tempCashier->setSurname(surname);
            tempCashier->setPatronymic(patronymic);
            tempMap.insert(make_pair(rows+1, tempCashier));
            cashCashiers.setElementDataById(cashCashiers.getSize() - 1, tempMap);
        }
    }

    cashiersGateway.insert(name, surname, patronymic);
    cout << "Node inserted!" << endl;
}

void UserAction::updateCashiers() {
    bool exit = false;
    string id;
    map<int, Cashiers*> tempMap;
    int rows = cashiersGateway.getFullCountRows();
    while(true) {
        cout << "Enter N nodes: " << endl;
        id = enterString();
        if(isOnlyInt(id) && stoi(id) <= rows) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    string column;
    while(true) {
        cout << "1)name" << endl;
        cout << "2)surname" << endl;
        cout << "3)patronymic" << endl;
        cout << "Enter column: " << endl;
        column = enterString();
        if(stoi(column) >= 1 && stoi(column) <= 3 && isOnlyInt(column)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    int columnInt = stoi(column);
    string columnName;
    switch(columnInt) {
    case 1:
        columnName = "name";
        break;
    case 2:
        columnName = "surname";
        break;
    case 3:
        columnName = "patronymic";
        break;
    }

    string data;
    while(true) {
        cout << "Enter data: " << endl;
        data = enterString();

        if(stoi(column) >= 1 && stoi(column) <= 3 && isOnlyString(data) && data.size() > 0 && data.size() <= 50) {
            break;
        }
        cout << "Incorrect value!" << endl;
    }
    bool checkCash = false;
    for(int i = 0; i < cashCashiers.getSize(); i++) {
        tempMap = cashCashiers.getElementDataById(i);
        if (tempMap.find(stoi(id)) != tempMap.end()) {
            checkCash = true;
            Cashiers *tempCashier = tempMap.at(stoi(id));
            switch(columnInt) {
            case 1:
                tempCashier->setName(data);
                break;
            case 2:
                tempCashier->setSurname(data);
                break;
            case 3:
                tempCashier->setPatronymic(data);
                break;
            }
            tempMap[stoi(id)] = tempCashier;
            cashCashiers.setElementDataById(i, tempMap);
            break;
        }
    }
    if(!checkCash) {
        cashiersGateway.loadRangeData(tempMap, stoi(id), stoi(id));
    }
    cashiersGateway.update(stoi(tempMap.at(stoi(id))->getId()), columnName, data);
    cout << "Node updated!" << endl;
}

void UserAction::deleteCashiers() {
    int rows = cashiersGateway.getFullCountRows();
    string id;
    while(true) {
        cout << "Enter N nodes: " << endl;
        id = enterString();
        if(isOnlyInt(id) && stoi(id) <= rows) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    map<int, Cashiers*> tempMap;
    int idDel;
    bool checkCash = false;
    for(int i = 0; i < cashCashiers.getSize(); i++) {
        tempMap = cashCashiers.getElementDataById(i);
        if (tempMap.find(stoi(id)) != tempMap.end()) {
            checkCash = true;
            idDel = i;
            break;
        }
    }
    if(!checkCash) {
        idDel = 0;
        cashiersGateway.loadRangeData(tempMap, stoi(id), stoi(id));
    }

    int tempId;
        for(int i = idDel, tempId = stoi(id); i < cashCashiers.getSize();) {
            map<int, Cashiers*> tempMap1;
            tempMap1 = cashCashiers.getElementDataById(i);
            if (!(tempMap1.find(tempId) != tempMap1.end())) {
                tempId++;
                continue;
            }
            for(int j = 0; j < tempMap1.size(); j++) {
                if (!(tempMap1.find(tempId+1) != tempMap1.end())) {
                    break;
                }
                tempMap1[tempId] = tempMap1[tempId+1];
                tempId++;
            }

            if(i+1 != cashCashiers.getSize()) {
                map<int, Cashiers*> tempMap2;
                tempMap2 = cashCashiers.getElementDataById(i+1);
                tempMap1[tempId] = tempMap2[tempId+1];
                tempId++;
            } else {
                if (tempMap1.find(rows) != tempMap1.end()) {
                    tempMap1.erase(tempId);
                } else {
                    map<int, Cashiers*> tempMap2;
                    cashiersGateway.loadRangeData(tempMap2, tempId+1, tempId+1);
                    tempMap1[tempId] = tempMap2[tempId+1];
                }
            }
            if(tempMap1.empty()) {
                cashCashiers.Prev();
                cashCashiers.delToEnd();
                pageCashiers--;
            } else {
                cashCashiers.setElementDataById(i, tempMap1);
            }
            i++;
        }
    cashiersGateway.del(stoi(tempMap.at(stoi(id))->getId()));
    cout << "Node deleted!" << endl;
}

void UserAction::clearCashCashiers() {
    pageCashiers = 1;
    cashCashiers.clear();
}

void UserAction::loadCashCashiers() {
    pageCashiers = 1;
    map<int, Cashiers*> mapCashiers;
    cashiersGateway.loadRangeData(mapCashiers, 1, countObjectOnPage);
    cashCashiers.addToEnd(mapCashiers);
}

void UserAction::viewCurrencies() {
    if(cashCurrencies.getNow().empty()) {
        cout << "Object is empty!" << endl;
    } else {
        bool exit = false;
        int id1 = 1 + (pageCurrencies - 1) * countObjectOnPage;
        int id2 = countObjectOnPage + (pageCurrencies - 1) * countObjectOnPage;
        int rows = currenciesGateway.getFullCountRows();
        while(!exit) {
            cout << setfill('-') << right << "+" << setw(4) << "+" << setw(10) << "+" << setw(10) << "+" << endl;
            cout << setfill(' ') << left << "| " << setw(2) << "N" << "| " << setw(8) << "code"
            << "| " << setw(8) << "name" << "| " << endl;
            cout << setfill('-') << right << "+" << setw(4) << "+" << setw(10) << "+" << setw(10) << "+" << endl;
            for(int i = id1, j = 0; j <  cashCurrencies.getNow().size(); i++, j++) {
                cout << setfill(' ') << left
                << "| " << setw(2) << i
                << "| " << setw(8) << cashCurrencies.getNow().at(i)->getCode()
                << "| " << setw(8) << cashCurrencies.getNow().at(i)->getName() << "| " << endl;
                cout << setfill('-') << right << "+" << setw(4) << "+" << setw(10) << "+" << setw(10) << "+" << endl;
            }
            int maxPage = rows % countObjectOnPage == 0 ? rows / countObjectOnPage : rows / countObjectOnPage + 1;
            cout << "pages: " << pageCurrencies << "/" << maxPage << endl;
            cout << "1) next" << endl;
            cout << "2) prev" << endl;
            cout << "3) Exit" << endl;
            cout << "Enter action: " << endl;
            int action = enterNumber(1,3);
            switch (action) {
            case 1: {
                if(pageCurrencies < maxPage) {
                    id1 += countObjectOnPage;
                    id2 += countObjectOnPage;
                    if(cashCurrencies.isNextNull()) {
                        map<int, Currencies*> mapCurrencies;
                        currenciesGateway.loadRangeData(mapCurrencies, id1, id2);
                        cashCurrencies.addToEnd(mapCurrencies);
                    } else {
                        cashCurrencies.Next();
                    }
                    pageCurrencies++;
                }
                break;
            }
            case 2: {
                if(pageCurrencies > 1) {
                    id1 -= countObjectOnPage;
                    id2 -= countObjectOnPage;
                    if(cashCurrencies.isPrevNull()) {
                        map<int, Currencies*> mapCurrencies;
                        currenciesGateway.loadRangeData(mapCurrencies, id1, id2);
                        cashCurrencies.addToBegin(mapCurrencies);
                    } else {
                        cashCurrencies.Prev();
                    }
                    pageCurrencies--;
                }
                break;
            }
            case 3: {
                exit = true;
                break;
            }
            default:
                cout << "Incorrect value!" << endl;
                break;
            }
        }
    }
}

void UserAction::insertCurrencies() {
    int rows = currenciesGateway.getFullCountRows();
    string code;
    while(true) {
        cout << "Enter code: " << endl;
        code = enterString();
        if(code.size() > 0 && code.size() <= 3 && isOnlyInt(code)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string name;
    while(true) {
        cout << "Enter name: " << endl;
        name = enterString();
        if(name.size() > 0 && name.size() <= 3 && isOnlyString(name)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    map<int, Currencies*> tempMap;
    tempMap = cashCurrencies.getElementDataById(cashCurrencies.getSize() - 1);
    int id = getRandomInt(100, 10000);
    if (tempMap.find(rows) != tempMap.end()) {
        if(tempMap.size() < countObjectOnPage) {
            Currencies *tempCurrencie = new Currencies;
            tempCurrencie->setId(to_string(rows+1));
            tempCurrencie->setCode(code);
            tempCurrencie->setName(name);
            tempMap.insert(make_pair(rows+1, tempCurrencie));
            cashCurrencies.setElementDataById(cashCurrencies.getSize() - 1, tempMap);
        }
    }

    currenciesGateway.insert(code, name);
    cout << "Node inserted!" << endl;
}

void UserAction::updateCurrencies() {
    bool exit = false;
    string id;
    map<int, Currencies*> tempMap;
    int rows = currenciesGateway.getFullCountRows();
    while(true) {
        cout << "Enter N nodes: " << endl;
        id = enterString();
        if(isOnlyInt(id) && stoi(id) <= rows) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    string column;
    while(true) {
        cout << "1)code" << endl;
        cout << "2)name" << endl;
        cout << "Enter column: " << endl;
        column = enterString();
        if(stoi(column) >= 1 && stoi(column) <= 2 && isOnlyInt(column)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    int columnInt = stoi(column);
    string columnName;
    switch(columnInt) {
    case 1:
        columnName = "code";
        break;
    case 2:
        columnName = "name";
        break;
    }

    string data;
    while(true) {
        cout << "Enter data: " << endl;
        data = enterString();

        if(stoi(column) == 1 && isOnlyInt(data) && data.size() == 3) {
            break;
        }
        if(stoi(column) == 2 && isOnlyString(data) && data.size() > 0 && data.size() <= 3) {
            break;
        }
        cout << "Incorrect value!" << endl;
    }
    bool checkCash = false;
    for(int i = 0; i < cashCurrencies.getSize(); i++) {
        tempMap = cashCurrencies.getElementDataById(i);
        if (tempMap.find(stoi(id)) != tempMap.end()) {
            checkCash = true;
            Currencies *tempCurrencie = tempMap.at(stoi(id));
            switch(columnInt) {
            case 1:
                tempCurrencie->setCode(data);
                break;
            case 2:
                tempCurrencie->setName(data);
                break;
            }
            tempMap[stoi(id)] = tempCurrencie;
            cashCurrencies.setElementDataById(i, tempMap);
            break;
        }
    }
    if(!checkCash) {
        currenciesGateway.loadRangeData(tempMap, stoi(id), stoi(id));
    }
    currenciesGateway.update(stoi(tempMap.at(stoi(id))->getId()), columnName, data);
    cout << "Node updated!" << endl;
}

void UserAction::deleteCurrencies() {
    int rows = currenciesGateway.getFullCountRows();
    string id;
    while(true) {
        cout << "Enter N nodes: " << endl;
        id = enterString();
        if(isOnlyInt(id) && stoi(id) <= rows) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    map<int, Currencies*> tempMap;
    int idDel;
    bool checkCash = false;
    for(int i = 0; i < cashCurrencies.getSize(); i++) {
        tempMap = cashCurrencies.getElementDataById(i);
        if (tempMap.find(stoi(id)) != tempMap.end()) {
            checkCash = true;
            idDel = i;
            break;
        }
    }
    if(!checkCash) {
        idDel = 0;
        currenciesGateway.loadRangeData(tempMap, stoi(id), stoi(id));
    }

    int tempId;
        for(int i = idDel, tempId = stoi(id); i < cashCurrencies.getSize();) {
            map<int, Currencies*> tempMap1;
            tempMap1 = cashCurrencies.getElementDataById(i);
            if (!(tempMap1.find(tempId) != tempMap1.end())) {
                tempId++;
                continue;
            }
            for(int j = 0; j < tempMap1.size(); j++) {
                if (!(tempMap1.find(tempId+1) != tempMap1.end())) {
                    break;
                }
                tempMap1[tempId] = tempMap1[tempId+1];
                tempId++;
            }

            if(i+1 != cashCurrencies.getSize()) {
                map<int, Currencies*> tempMap2;
                tempMap2 = cashCurrencies.getElementDataById(i+1);
                tempMap1[tempId] = tempMap2[tempId+1];
                tempId++;
            } else {
                if (tempMap1.find(rows) != tempMap1.end()) {
                    tempMap1.erase(tempId);
                } else {
                    map<int, Currencies*> tempMap2;
                    currenciesGateway.loadRangeData(tempMap2, tempId+1, tempId+1);
                    tempMap1[tempId] = tempMap2[tempId+1];
                }
            }
            if(tempMap1.empty()) {
                cashCurrencies.Prev();
                cashCurrencies.delToEnd();
                pageCurrencies--;
            } else {
                cashCurrencies.setElementDataById(i, tempMap1);
            }
            i++;
        }
    currenciesGateway.del(stoi(tempMap.at(stoi(id))->getId()));
    cout << "Node deleted!" << endl;
}

void UserAction::clearCashCurrencies() {
    pageCurrencies = 1;
    cashCurrencies.clear();
}

void UserAction::loadCashCurrencies() {
    pageCurrencies = 1;
    map<int, Currencies*> mapCurrencies;
    currenciesGateway.loadRangeData(mapCurrencies, 1, countObjectOnPage);
    cashCurrencies.addToEnd(mapCurrencies);
}

void UserAction::viewRates() {
    if(cashRates.getNow().empty()) {
        cout << "Object is empty!" << endl;
    } else {
        bool exit = false;
        int id1 = 1 + (pageRates - 1) * countObjectOnPage;
        int id2 = countObjectOnPage + (pageRates - 1) * countObjectOnPage;
        int rows = ratesGateway.getFullCountRows();
        while(!exit) {
            cout << setfill('-') << right << "+" << setw(4) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << endl;
            cout << setfill(' ') << left
            << "| " << setw(2) << "N"
            << "| " << setw(18) << "sold"
            << "| " << setw(18) << "purchased"
            << "| " << setw(18) << "sale_rate"
            << "| " << setw(18) << "purchase_rate" << "| " << endl;
             cout << setfill('-') << right << "+" << setw(4) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << endl;
            for(int i = id1, j = 0; j <  cashRates.getNow().size(); i++, j++) {
                cout << setfill(' ') << left
                << "| " << setw(2) << i
                << "| " << setw(18) << cashRates.getNow().at(i)->getCurrencySold().at(1)->getName()
                << "| " << setw(18) << cashRates.getNow().at(i)->getCurrencyPurchased().at(1)->getName()
                << "| " << setw(18) << cashRates.getNow().at(i)->getSaleRate()
                << "| " << setw(18) << cashRates.getNow().at(i)->getPurchaseRate() << "| " << endl;
                 cout << setfill('-') << right << "+" << setw(4) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << setw(20) << "+" << endl;
            }
            int maxPage = rows % countObjectOnPage == 0 ? rows / countObjectOnPage : rows / countObjectOnPage + 1;
            cout << "pages: " << pageRates << "/" << maxPage << endl;
            cout << "1) next" << endl;
            cout << "2) prev" << endl;
            cout << "3) Exit" << endl;
            cout << "Enter action: " << endl;
            int action = enterNumber(1,3);
            switch (action) {
            case 1: {
                if(pageRates < maxPage) {
                    id1 += countObjectOnPage;
                    id2 += countObjectOnPage;
                    if(cashRates.isNextNull()) {
                        map<int, Rates*> mapRates;
                        ratesGateway.loadRangeData(mapRates, cashCurrencies, id1, id2);
                        cashRates.addToEnd(mapRates);
                    } else {
                        cashRates.Next();
                    }
                    pageRates++;
                }
                break;
            }
            case 2: {
                if(pageRates > 1) {
                    id1 -= countObjectOnPage;
                    id2 -= countObjectOnPage;
                    if(cashRates.isPrevNull()) {
                        map<int, Rates*> mapRates;
                        ratesGateway.loadRangeData(mapRates, cashCurrencies, id1, id2);
                        cashRates.addToBegin(mapRates);
                    } else {
                        cashRates.Prev();
                    }
                    pageRates--;
                }
                break;
            }
            case 3: {
                exit = true;
                break;
            }
            default:
                cout << "Incorrect value!" << endl;
                break;
            }
        }
    }
}

void UserAction::insertRates() {
    map<int, Rates*> tempMap;
    map<int, Currencies*> tempMap2;
    int rows = ratesGateway.getFullCountRows();
    int rowsCurrencies = currenciesGateway.getFullCountRows();
    string N_currency_sold;
    while(true) {
        cout << "Enter N currencies sold: " << endl;
        N_currency_sold = enterString();
        if(stoi(N_currency_sold) > 0 && stoi(N_currency_sold) <= rowsCurrencies && isOnlyInt(N_currency_sold)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string N_currency_purchased;
    while(true) {
        cout << "Enter N currencies purchased: " << endl;
         N_currency_purchased = enterString();
        if(stoi( N_currency_purchased) > 0 && stoi(N_currency_purchased) <= rowsCurrencies && isOnlyInt(N_currency_purchased)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string sale_rate;
    while(true) {
        cout << "Enter sale rate: " << endl;
        sale_rate = enterString();
        if(sale_rate.size() > 0 && sale_rate.size() <= 10 && isOnlyInt(sale_rate)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string purchase_rate;
    while(true) {
        cout << "Enter purchase rate: " << endl;
        purchase_rate = enterString();
        if(purchase_rate.size() > 0 && purchase_rate.size() <= 10 && isOnlyInt(purchase_rate)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    string id_currency_sold;
    string id_currency_purchased;
    bool check = false;
    for(int i = 0; i < cashCurrencies.getSize(); i++) {
        tempMap2 = cashCurrencies.getElementDataById(i);
        if (tempMap2.find(stoi(N_currency_sold)) != tempMap2.end()) {
            id_currency_sold = cashCurrencies.getElementDataById(i).at(stoi(N_currency_sold))->getId();
            check = true;
            break;
        }

    }

    if(!check) {
        map<int, Currencies*> mapCurrencies;
        currenciesGateway.loadRangeData(mapCurrencies, stoi(N_currency_sold), stoi(N_currency_sold));
        id_currency_sold = mapCurrencies.at(stoi(N_currency_sold))->getId();
    }

    check = false;

    for(int i = 0; i < cashCurrencies.getSize(); i++) {
        tempMap2 = cashCurrencies.getElementDataById(i);
        if (tempMap2.find(stoi(N_currency_purchased)) != tempMap2.end()) {
            id_currency_purchased = cashCurrencies.getElementDataById(i).at(stoi(N_currency_purchased))->getId();
            check = true;
            break;
        }

    }

    if(!check) {
        map<int, Currencies*> mapCurrencies;
        currenciesGateway.loadRangeData(mapCurrencies, stoi(N_currency_purchased), stoi(N_currency_purchased));
        id_currency_purchased = mapCurrencies.at(stoi(N_currency_purchased))->getId();
    }

    tempMap = cashRates.getElementDataById(cashRates.getSize() - 1);
    if (tempMap.find(rows) != tempMap.end()) {
        if(tempMap.size() < countObjectOnPage) {
            bool check2 = false;
            Rates *tempRates = new Rates;
            tempRates->setId(to_string(rows+1));
            Currencies *currenciesSold;
            map<int, Currencies*> currencySold;
            for(int k = 0; k < cashCurrencies.getSize(); k++) {
                map<int, Currencies*> tempMap = cashCurrencies.getElementDataById(k);
                for (map<int, Currencies*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                    if(stoi(it->second->getId()) == stoi(id_currency_sold)) {
                        currenciesSold = cashCurrencies.getElementDataById(k).at(it->first);
                        check2 = true;
                        break;
                    }
                }
            }

            if(!check2) {
                currenciesSold = new Currencies();
                currenciesGateway.loadDataById(currenciesSold, stoi(id_currency_sold));
            }
            check2 = false;
            currencySold.insert(make_pair(1, currenciesSold));
            tempRates->setCurrencySold(currencySold);

            Currencies *currenciesPurchased;
            map<int, Currencies*> currencyPurchased;
            for(int k = 0; k < cashCurrencies.getSize(); k++) {
                map<int, Currencies*> tempMap = cashCurrencies.getElementDataById(k);
                for (map<int, Currencies*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                    if(stoi(it->second->getId()) == stoi(id_currency_purchased)) {
                        currenciesPurchased = cashCurrencies.getElementDataById(k).at(it->first);
                        check2 = true;
                        break;
                    }
                }
            }

            if(!check2) {
                currenciesPurchased = new Currencies();
                currenciesGateway.loadDataById(currenciesPurchased, stoi(id_currency_purchased));
            }

            currencyPurchased.insert(make_pair(1, currenciesPurchased));
            tempRates->setCurrencyPurchased(currencyPurchased);

            tempRates->setSaleRate(sale_rate);
            tempRates->setPurchaseRate(purchase_rate);
            tempMap.insert(make_pair(rows+1, tempRates));
            cashRates.setElementDataById(cashRates.getSize() - 1, tempMap);
        }
    }

    ratesGateway.insert(id_currency_sold, id_currency_purchased, sale_rate, purchase_rate);
    cout << "Node inserted!" << endl;
}

void UserAction::updateRates() {
    string id;
    map<int, Rates*> tempMap;
    int rows = ratesGateway.getFullCountRows();
    int rowsCurrencies = currenciesGateway.getFullCountRows();
    while(true) {
        cout << "Enter N nodes: " << endl;
        id = enterString();
        if(isOnlyInt(id) && stoi(id) <= rows) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    string column;
    while(true) {
        cout << "1)sold" << endl;
        cout << "2)purchased" << endl;
        cout << "3)sale_rate" << endl;
        cout << "4)purchase_rate" << endl;
        cout << "Enter column: " << endl;
        column = enterString();
        if(stoi(column) >= 1 && stoi(column) <= 4 && isOnlyInt(column)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    int columnInt = stoi(column);
    string columnName;
    switch(columnInt) {
    case 1:
        columnName = "id_currency_sold";
        break;
    case 2:
        columnName = "id_currency_purchased";
        break;
    case 3:
        columnName = "sale_rate";
        break;
    case 4:
        columnName = "purchase_rate";
        break;
    }

    string data;
    while(true) {
        if(stoi(column) == 1) {
            cout << "Enter N currencies sold: " << endl;
            data = enterString();
            if(stoi(data) > 0 && stoi(data) <= rowsCurrencies && isOnlyInt(data)) {
                bool check = false;
                map<int, Currencies*> tempMap2;
                for(int i = 0; i < cashCurrencies.getSize(); i++) {
                    tempMap2 = cashCurrencies.getElementDataById(i);
                    if (tempMap2.find(stoi(data)) != tempMap2.end()) {
                        data = cashCurrencies.getElementDataById(i).at(stoi(data))->getId();
                        check = true;
                        break;
                    }

                }

                if(!check) {
                    map<int, Currencies*> mapCurrencies;
                    currenciesGateway.loadRangeData(mapCurrencies, stoi(data), stoi(data));
                    data = mapCurrencies.at(stoi(data))->getId();
                }
                break;
            }
        }

        if(stoi(column) == 2) {
            cout << "Enter N currencies purchased: " << endl;
            data = enterString();
            if(stoi(data) > 0 && stoi(data) <= rowsCurrencies && isOnlyInt(data)) {
                bool check = false;
                map<int, Currencies*> tempMap2;
                for(int i = 0; i < cashCurrencies.getSize(); i++) {
                    tempMap2 = cashCurrencies.getElementDataById(i);
                    if (tempMap2.find(stoi(data)) != tempMap2.end()) {
                        data = cashCurrencies.getElementDataById(i).at(stoi(data))->getId();
                        check = true;
                        break;
                    }

                }

                if(!check) {
                    map<int, Currencies*> mapCurrencies;
                    currenciesGateway.loadRangeData(mapCurrencies, stoi(data), stoi(data));
                    data = mapCurrencies.at(stoi(data))->getId();
                }
                break;
            }
        }

        if(stoi(column) == 3) {
            cout << "Enter sale rate: " << endl;
            data = enterString();
            if(isOnlyIntAndPoint(data) && data.size() > 0 && data.size() < 20) {
                break;
            }
        }

        if(stoi(column) == 4) {
            cout << "Enter purchase rate: " << endl;
            data = enterString();
            if(isOnlyIntAndPoint(data) && data.size() > 0 && data.size() < 20) {
                break;
            }
        }
        cout << "Incorrect value!" << endl;
    }


    bool checkCash = false;
    for(int i = 0; i < cashRates.getSize(); i++) {
        tempMap = cashRates.getElementDataById(i);
        if (tempMap.find(stoi(id)) != tempMap.end()) {
            checkCash = true;
            Rates *tempRates = tempMap.at(stoi(id));
            switch(columnInt) {
            case 1: {
                bool check2 = false;
                Currencies *currenciesSold;
                map<int, Currencies*> currencySold;
                for(int k = 0; k < cashCurrencies.getSize(); k++) {
                    map<int, Currencies*> tempMap = cashCurrencies.getElementDataById(k);
                    for (map<int, Currencies*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                        if(stoi(it->second->getId()) == stoi(data)) {
                            currenciesSold = cashCurrencies.getElementDataById(k).at(it->first);
                            check2 = true;
                            break;
                        }
                    }
                }

                if(!check2) {
                    currenciesSold = new Currencies();
                    currenciesGateway.loadDataById(currenciesSold, stoi(data));
                }
                currencySold.insert(make_pair(1, currenciesSold));
                tempRates->setCurrencySold(currencySold);
                break;
            }
            case 2: {
                bool check2 = false;
                Currencies *currenciesPurchased;
                map<int, Currencies*> currencyPurchased;
                for(int k = 0; k < cashCurrencies.getSize(); k++) {
                    map<int, Currencies*> tempMap = cashCurrencies.getElementDataById(k);
                    for (map<int, Currencies*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                        if(stoi(it->second->getId()) == stoi(data)) {
                            currenciesPurchased = cashCurrencies.getElementDataById(k).at(it->first);
                            check2 = true;
                            break;
                        }
                    }
                }

                if(!check2) {
                    currenciesPurchased = new Currencies();
                    currenciesGateway.loadDataById(currenciesPurchased, stoi(data));
                }

                currencyPurchased.insert(make_pair(1, currenciesPurchased));
                tempRates->setCurrencyPurchased(currencyPurchased);
                break;
            }
            case 3: {
                tempRates->setSaleRate(data);
                break;
            }
            case 4: {
                    tempRates->setPurchaseRate(data);
                    break;
                }
            }
            tempMap[stoi(id)] = tempRates;
            cashRates.setElementDataById(i, tempMap);
            break;
        }
    }
    if(!checkCash) {
        ratesGateway.loadRangeData(tempMap, cashCurrencies, stoi(id), stoi(id));
    }
    ratesGateway.update(stoi(tempMap.at(stoi(id))->getId()), columnName, data);
    cout << "Node updated!" << endl;
}

void UserAction::deleteRates() {
    int rows = ratesGateway.getFullCountRows();
    string id;
    while(true) {
        cout << "Enter N nodes: " << endl;
        id = enterString();
        if(isOnlyInt(id) && stoi(id) <= rows) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    map<int, Rates*> tempMap;
    int idDel;
    bool checkCash = false;
    for(int i = 0; i < cashRates.getSize(); i++) {
        tempMap = cashRates.getElementDataById(i);
        if (tempMap.find(stoi(id)) != tempMap.end()) {
            checkCash = true;
            idDel = i;
            break;
        }
    }
    if(!checkCash) {
        idDel = 0;
        ratesGateway.loadRangeData(tempMap, cashCurrencies, stoi(id), stoi(id));
    }

    int tempId;
        for(int i = idDel, tempId = stoi(id); i < cashRates.getSize();) {
            map<int, Rates*> tempMap1;
            tempMap1 = cashRates.getElementDataById(i);
            if (!(tempMap1.find(tempId) != tempMap1.end())) {
                tempId++;
                continue;
            }
            for(int j = 0; j < tempMap1.size(); j++) {
                if (!(tempMap1.find(tempId+1) != tempMap1.end())) {
                    break;
                }
                tempMap1[tempId] = tempMap1[tempId+1];
                tempId++;
            }

            if(i+1 != cashRates.getSize()) {
                map<int, Rates*> tempMap2;
                tempMap2 = cashRates.getElementDataById(i+1);
                tempMap1[tempId] = tempMap2[tempId+1];
                tempId++;
            } else {
                if (tempMap1.find(rows) != tempMap1.end()) {
                    tempMap1.erase(tempId);
                } else {
                    map<int, Rates*> tempMap2;
                    ratesGateway.loadRangeData(tempMap2, cashCurrencies, tempId+1, tempId+1);
                    tempMap1[tempId] = tempMap2[tempId+1];
                }
            }
            if(tempMap1.empty()) {
                cashRates.Prev();
                cashRates.delToEnd();
                pageRates--;
            } else {
                cashRates.setElementDataById(i, tempMap1);
            }
            i++;
        }
    ratesGateway.del(stoi(tempMap.at(stoi(id))->getId()));
    cout << "Node deleted!" << endl;
}

void UserAction::clearCashRates() {
    pageRates = 1;
    cashRates.clear();
}

void UserAction::loadCashRates() {
    pageRates = 1;
    map<int, Rates*> mapRates;
    ratesGateway.loadRangeData(mapRates, cashCurrencies, 1, countObjectOnPage);
    cashRates.addToEnd(mapRates);
}

void UserAction::viewTransactions() {
    if(cashTransactions.getNow().empty()) {
        cout << "Object is empty!" << endl;
    } else {
        bool exit = false;
        int id1 = 1 + (pageTransactions - 1) * countObjectOnPage;
        int id2 = countObjectOnPage + (pageTransactions - 1) * countObjectOnPage;
        int rows = transactionsGateway.getFullCountRows();
        while(!exit) {
            cout << setfill('-') << right << "+" << setw(4) << "+" << setw(15) << "+" << setw(15) << "+" << setw(15) << "+" << setw(15) << "+" << setw(20) << "+" << setw(20)
            << "+" << setw(15) << "+" << setw(15) << "+" << setw(20) << "+" << setw(20)  << "+" << endl;
            cout << setfill(' ') << left
            << "| " << setw(2) << "N"
            << "| " << setw(13) << "sold"
            << "| " << setw(13) << "purchased"
            << "| " << setw(13) << "client"
            << "| " << setw(13) << "cashier"
            << "| " << setw(18) << "rate_sold"
            << "| " << setw(18) << "rate_purchased"
            << "| " << setw(13) << "date"
            << "| " << setw(13) << "time"
            << "| " << setw(18) << "sum_sold"
            << "| " << setw(18) << "sum_purchased" << "| " << endl;
            cout << setfill('-') << right << "+" << setw(4) << "+" << setw(15) << "+" << setw(15) << "+" << setw(15) << "+" << setw(15) << "+" << setw(20) << "+" << setw(20)
            << "+" << setw(15) << "+" << setw(15) << "+" << setw(20) << "+" << setw(20)  << "+" << endl;
            for(int i = id1, j = 0; j <  cashTransactions.getNow().size(); i++, j++) {
                cout << setfill(' ') << left
                << "| " << setw(2) << i
                << "| " << setw(13) << cashTransactions.getNow().at(i)->getCurrencySold().at(1)->getName()
                << "| " << setw(13) << cashTransactions.getNow().at(i)->getCurrencyPurchased().at(1)->getName()
                << "| " << setw(13) << cashTransactions.getNow().at(i)->getClient().at(1)->getSurname()
                << "| " << setw(13) << cashTransactions.getNow().at(i)->getCashier().at(1)->getSurname()
                << "| " << setw(18) << cashTransactions.getNow().at(i)->getRateSold().at(1)->getSaleRate()
                << "| " << setw(18) << cashTransactions.getNow().at(i)->getRatePurchased().at(1)->getPurchaseRate()
                << "| " << setw(13) << cashTransactions.getNow().at(i)->getDate()
                << "| " << setw(13) << cashTransactions.getNow().at(i)->getTime()
                << "| " << setw(18) << cashTransactions.getNow().at(i)->getSumCurrencySold()
                << "| " << setw(18) << cashTransactions.getNow().at(i)->getSumCurrencyPurchased() << "| " << endl;
                cout << setfill('-') << right << "+" << setw(4) << "+" << setw(15) << "+" << setw(15) << "+" << setw(15) << "+" << setw(15) << "+" << setw(20) << "+" << setw(20)
                << "+" << setw(15) << "+" << setw(15) << "+" << setw(20) << "+" << setw(20)  << "+" << endl;
            }
            int maxPage = rows % countObjectOnPage == 0 ? rows / countObjectOnPage : rows / countObjectOnPage + 1;
            cout << "pages: " << pageTransactions << "/" << maxPage << endl;
            cout << "1) next" << endl;
            cout << "2) prev" << endl;
            cout << "3) Exit" << endl;
            cout << "Enter action: " << endl;
            int action = enterNumber(1,3);
            switch (action) {
            case 1: {
                if(pageTransactions < maxPage) {
                    id1 += countObjectOnPage;
                    id2 += countObjectOnPage;
                    if(cashTransactions.isNextNull()) {
                        map<int, Transactions*> mapTransactions;
                        transactionsGateway.loadRangeData(mapTransactions, cashClients, cashCashiers, cashCurrencies, cashRates, id1, id2);
                        cashTransactions.addToEnd(mapTransactions);
                    } else {
                        cashTransactions.Next();
                    }
                    pageTransactions++;
                }
                break;
            }
            case 2: {
                if(pageTransactions > 1) {
                    id1 -= countObjectOnPage;
                    id2 -= countObjectOnPage;
                    if(cashTransactions.isPrevNull()) {
                        map<int, Transactions*> mapTransactions;
                        transactionsGateway.loadRangeData(mapTransactions, cashClients, cashCashiers, cashCurrencies, cashRates, id1, id2);
                        cashTransactions.addToBegin(mapTransactions);
                    } else {
                        cashTransactions.Prev();
                    }
                    pageTransactions--;
                }
                break;
            }
            case 3: {
                exit = true;
                break;
            }
            default:
                cout << "Incorrect value!" << endl;
                break;
            }
        }
    }
}

void UserAction::insertTransactions() {
    map<int, Transactions*> tempMap;
    map<int, Currencies*> tempCurrencies;
    map<int, Clients*> tempClients;
    map<int, Cashiers*> tempCashiers;
    map<int, Rates*> tempRates;
    int rows = transactionsGateway.getFullCountRows();
    int rowsCurrencies = currenciesGateway.getFullCountRows();
    int rowsClients = clientsGateway.getFullCountRows();
    int rowsCashiers = cashiersGateway.getFullCountRows();
    int rowsRates = ratesGateway.getFullCountRows();
    string N_currency_sold;
    string id_currency_sold;
    while(true) {
        cout << "Enter N currencies sold: " << endl;
        N_currency_sold = enterString();
        if(stoi(N_currency_sold) > 0 && stoi(N_currency_sold) <= rowsCurrencies && isOnlyInt(N_currency_sold)) {
            bool checkR = false;
            for(int i = 0; i < cashCurrencies.getSize(); i++) {
                tempCurrencies = cashCurrencies.getElementDataById(i);
                if (tempCurrencies.find(stoi(N_currency_sold)) != tempCurrencies.end()) {
                    id_currency_sold = cashCurrencies.getElementDataById(i).at(stoi(N_currency_sold))->getId();
                    checkR = true;
                    break;
                }

            }

            if(!checkR) {
                map<int, Currencies*> mapCurrencies;
                currenciesGateway.loadRangeData(mapCurrencies, stoi(N_currency_sold), stoi(N_currency_sold));
                id_currency_sold = mapCurrencies.at(stoi(N_currency_sold))->getId();
            }
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string N_currency_purchased;
    string id_currency_purchased;
    while(true) {
        cout << "Enter N currencies purchased: " << endl;
        N_currency_purchased = enterString();
        if(stoi(N_currency_purchased) != stoi(N_currency_sold) && stoi( N_currency_purchased) > 0 && stoi(N_currency_purchased) <= rowsCurrencies && isOnlyInt(N_currency_purchased)) {
            bool checkR = false;

            for(int i = 0; i < cashCurrencies.getSize(); i++) {
                tempCurrencies = cashCurrencies.getElementDataById(i);
                if (tempCurrencies.find(stoi(N_currency_purchased)) != tempCurrencies.end()) {
                    id_currency_purchased = cashCurrencies.getElementDataById(i).at(stoi(N_currency_purchased))->getId();
                    checkR = true;
                    break;
                }

            }

            if(!checkR) {
                map<int, Currencies*> mapCurrencies;
                currenciesGateway.loadRangeData(mapCurrencies, stoi(N_currency_purchased), stoi(N_currency_purchased));
                id_currency_purchased = mapCurrencies.at(stoi(N_currency_purchased))->getId();
            }
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string N_client;
    while(true) {
        cout << "Enter N client: " << endl;
        N_client = enterString();
        if(stoi(N_client) > 0 && stoi(N_client) <= rowsClients && isOnlyInt(N_client)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string N_cashier;
    while(true) {
        cout << "Enter N cashier: " << endl;
        N_cashier = enterString();
        if(stoi(N_cashier) > 0 && stoi(N_cashier) <= rowsCashiers && isOnlyInt(N_cashier)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    bool checkRatesSold = false;
    bool checkRatesPurchased = false;
    string N_rate_sold;
    string rate_sold;
    string id_rate_sold;
    while(true) {
        cout << "Enter N rate sold: " << endl;
        N_rate_sold = enterString();
        if(stoi(N_rate_sold) > 0 && stoi(N_rate_sold) <= rowsRates && isOnlyInt(N_rate_sold)) {
            bool checkR = false;
            Currencies *currenciesSold = new Currencies();
            currenciesGateway.loadDataById(currenciesSold, stoi(id_currency_sold));
            for(int i = 0; i < cashRates.getSize(); i++) {
                tempRates = cashRates.getElementDataById(i);
                if (tempRates.find(stoi(N_rate_sold)) != tempRates.end()) {
                    id_rate_sold = cashRates.getElementDataById(i).at(stoi(N_rate_sold))->getId();
                    rate_sold = cashRates.getElementDataById(i).at(stoi(N_rate_sold))->getSaleRate();
                    checkR = true;
                    if(stoi(currenciesSold->getId()) == stoi(cashRates.getElementDataById(i).at(stoi(N_rate_sold))->getCurrencySold().at(1)->getId())) {
                        checkRatesSold = true;
                    }
                    break;
                }
            }

            if(!checkR) {
                map<int, Rates*> mapRates;
                ratesGateway.loadRangeData(mapRates, cashCurrencies, stoi(N_rate_sold), stoi(N_rate_sold));
                id_rate_sold = mapRates.at(stoi(N_rate_sold))->getId();
                rate_sold = mapRates.at(stoi(N_rate_sold))->getSaleRate();
                if(stoi(currenciesSold->getId()) == stoi(mapRates.at(stoi(N_rate_sold))->getCurrencySold().at(1)->getId())) {
                    checkRatesSold = true;
                }
            }
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string N_rate_purchased;
    string rate_purchased;
    string id_rate_purchased;
    while(true) {
        cout << "Enter N rate purchased: " << endl;
        N_rate_purchased = enterString();
        if(stoi(N_rate_purchased) > 0 && stoi(N_rate_purchased) <= rowsRates && isOnlyInt(N_rate_purchased)) {
            bool checkR = false;
            Currencies *currenciesPurchased = new Currencies();
            currenciesGateway.loadDataById(currenciesPurchased, stoi(id_currency_purchased));
            for(int i = 0; i < cashRates.getSize(); i++) {
                tempRates = cashRates.getElementDataById(i);
                if (tempRates.find(stoi(N_rate_purchased)) != tempRates.end()) {
                    id_rate_purchased = cashRates.getElementDataById(i).at(stoi(N_rate_purchased))->getId();
                    rate_purchased = cashRates.getElementDataById(i).at(stoi(N_rate_purchased))->getPurchaseRate();
                    checkR = true;
                    if(stoi(currenciesPurchased->getId()) == stoi(cashRates.getElementDataById(i).at(stoi(N_rate_purchased))->getCurrencyPurchased().at(1)->getId())) {
                        checkRatesPurchased = true;
                    }
                    break;
                }

            }

            if(!checkR) {
                map<int, Rates*> mapRates;
                ratesGateway.loadRangeData(mapRates, cashCurrencies, stoi(N_rate_purchased), stoi(N_rate_purchased));
                id_rate_purchased = mapRates.at(stoi(N_rate_purchased))->getId();
                rate_purchased = mapRates.at(stoi(N_rate_purchased))->getPurchaseRate();
                if(stoi(currenciesPurchased->getId()) == stoi(mapRates.at(stoi(N_rate_purchased))->getCurrencyPurchased().at(1)->getId())) {
                    checkRatesPurchased = true;
                }
            }
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    if(!checkRatesSold || !checkRatesPurchased) {
        cout << "Error! The exchange rate does not match the currency" << endl;
    } else {
    string action;
    while(true) {
        cout << "Enter action:" << endl;
        cout << "1) buy currency" << endl;
        cout << "2) sell currency" << endl;
        action = enterString();
        if(stoi(action) >= 1 && stoi(action) <= 2 && isOnlyInt(action)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string sum;
    while(true) {
        cout << "Enter the amount of currency to transfer: " << endl;
        sum = enterString();
        if(sum.size() > 0 && sum.size() < 10 && isOnlyIntAndPoint(sum)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }

    string date = getDate();
    string time = getTime();
    string id_client;
    string id_cashier;

    bool check = false;

    for(int i = 0; i < cashClients.getSize(); i++) {
        tempClients = cashClients.getElementDataById(i);
        if (tempClients.find(stoi(N_client)) != tempClients.end()) {
            id_client = cashClients.getElementDataById(i).at(stoi(N_client))->getId();
            check = true;
            break;
        }

    }

    if(!check) {
        map<int, Clients*> mapClients;
        clientsGateway.loadRangeData(mapClients, stoi(N_client), stoi(N_client));
        id_client = mapClients.at(stoi(N_client))->getId();
    }

    check = false;

    for(int i = 0; i < cashCashiers.getSize(); i++) {
        tempCashiers = cashCashiers.getElementDataById(i);
        if (tempCashiers.find(stoi(N_cashier)) != tempCashiers.end()) {
            id_cashier = cashCashiers.getElementDataById(i).at(stoi(N_cashier))->getId();
            check = true;
            break;
        }

    }

    if(!check) {
        map<int, Cashiers*> mapCashiers;
        cashiersGateway.loadRangeData(mapCashiers, stoi(N_cashier), stoi(N_cashier));
        id_cashier = mapCashiers.at(stoi(N_cashier))->getId();
    }

    if(stoi(action) == 1) {
        rate_purchased = to_string(stod(sum) * stod(rate_sold));
        rate_sold = sum;
    }

    if(stoi(action) == 2) {
        rate_sold = to_string(stod(sum) / stod(rate_purchased));
        rate_purchased = sum;
    }

    tempMap = cashTransactions.getElementDataById(cashTransactions.getSize() - 1);
    if (tempMap.find(rows) != tempMap.end()) {
        if(tempMap.size() < countObjectOnPage) {
            bool check2 = false;
            Transactions *tempTransactions = new Transactions;
            tempTransactions->setId(to_string(rows+1));
            Currencies *currenciesSold;
            map<int, Currencies*> currencySold;
            for(int k = 0; k < cashCurrencies.getSize(); k++) {
                map<int, Currencies*> tempMap = cashCurrencies.getElementDataById(k);
                for (map<int, Currencies*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                    if(stoi(it->second->getId()) == stoi(id_currency_sold)) {
                        currenciesSold = cashCurrencies.getElementDataById(k).at(it->first);
                        check2 = true;
                        break;
                    }
                }
            }

            if(!check2) {
                currenciesSold = new Currencies();
                currenciesGateway.loadDataById(currenciesSold, stoi(id_currency_sold));
            }
            check2 = false;
            currencySold.insert(make_pair(1, currenciesSold));
            tempTransactions->setCurrencySold(currencySold);


            Currencies *currenciesPurchased;
            map<int, Currencies*> currencyPurchased;
            for(int k = 0; k < cashCurrencies.getSize(); k++) {
                map<int, Currencies*> tempMap = cashCurrencies.getElementDataById(k);
                for (map<int, Currencies*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                    if(stoi(it->second->getId()) == stoi(id_currency_purchased)) {
                        currenciesPurchased = cashCurrencies.getElementDataById(k).at(it->first);
                        check2 = true;
                        break;
                    }
                }
            }

            if(!check2) {
                currenciesPurchased = new Currencies();
                currenciesGateway.loadDataById(currenciesPurchased, stoi(id_currency_purchased));
            }

            check2 = false;
            currencyPurchased.insert(make_pair(1, currenciesPurchased));
            tempTransactions->setCurrencyPurchased(currencyPurchased);

            Clients *clients;
            map<int, Clients*> clientsMap;
            for(int k = 0; k < cashClients.getSize(); k++) {
                map<int, Clients*> tempMap = cashClients.getElementDataById(k);
                for (map<int, Clients*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                    if(stoi(it->second->getId()) == stoi(id_client)) {
                        clients = cashClients.getElementDataById(k).at(it->first);
                        check2 = true;
                        break;
                    }
                }
            }

            if(!check2) {
                clients = new Clients();
                clientsGateway.loadDataById(clients, stoi(id_client));
            }

            check2 = false;
            clientsMap.insert(make_pair(1, clients));
            tempTransactions->setClient(clientsMap);

            Cashiers *cashiers;
            map<int, Cashiers*> cashiersMap;
            for(int k = 0; k < cashCashiers.getSize(); k++) {
                map<int, Cashiers*> tempMap = cashCashiers.getElementDataById(k);
                for (map<int, Cashiers*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                    if(stoi(it->second->getId()) == stoi(id_cashier)) {
                        cashiers = cashCashiers.getElementDataById(k).at(it->first);
                        check2 = true;
                        break;
                    }
                }
            }

            if(!check2) {
                cashiers = new Cashiers();
                cashiersGateway.loadDataById(cashiers, stoi(id_cashier));
            }

            check2 = false;
            cashiersMap.insert(make_pair(1, cashiers));
            tempTransactions->setCashier(cashiersMap);

            Rates *rateSold;
            map<int, Rates*> ratesMap;
            for(int k = 0; k < cashRates.getSize(); k++) {
                map<int, Rates*> tempMap = cashRates.getElementDataById(k);
                for (map<int, Rates*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                    if(stoi(it->second->getId()) == stoi(id_rate_sold)) {
                        rateSold = cashRates.getElementDataById(k).at(it->first);
                        check2 = true;
                        break;
                    }
                }
            }

            if(!check2) {
                rateSold = new Rates();
                ratesGateway.loadDataById(rateSold, cashCurrencies, stoi(id_rate_sold));
            }

            check2 = false;
            ratesMap.insert(make_pair(1, rateSold));
            tempTransactions->setRateSold(ratesMap);

            Rates *ratePurchased;
            map<int, Rates*> rates2Map;
            for(int k = 0; k < cashRates.getSize(); k++) {
                map<int, Rates*> tempMap = cashRates.getElementDataById(k);
                for (map<int, Rates*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                    if(stoi(it->second->getId()) == stoi(id_rate_purchased)) {
                        ratePurchased = cashRates.getElementDataById(k).at(it->first);
                        check2 = true;
                        break;
                    }
                }
            }

            if(!check2) {
                ratePurchased = new Rates();
                ratesGateway.loadDataById(ratePurchased, cashCurrencies, stoi(id_rate_purchased));
            }

            check2 = false;
            rates2Map.insert(make_pair(1, ratePurchased));
            tempTransactions->setRatePurchased(rates2Map);

            tempTransactions->setDate(date);
            tempTransactions->setTime(time);
            tempTransactions->setSumCurrencySold(rate_sold);
            tempTransactions->setSumCurrencyPurchased(rate_purchased);
            tempMap.insert(make_pair(rows+1, tempTransactions));
            cashTransactions.setElementDataById(cashTransactions.getSize() - 1, tempMap);
        }
    }

    transactionsGateway.insert(id_currency_sold, id_currency_purchased, id_client, id_cashier, id_rate_sold,id_rate_purchased, date, time, rate_sold, rate_purchased);
    cout << "Node inserted!" << endl;
    }
}

void UserAction::updateTransactions() {
    string id;
    map<int, Transactions*> tempMap;
    int rows = ratesGateway.getFullCountRows();
    int rowsCurrencies = currenciesGateway.getFullCountRows();
    int rowsClients = clientsGateway.getFullCountRows();
    int rowsCashiers = cashiersGateway.getFullCountRows();
    int rowsRates = ratesGateway.getFullCountRows();
    while(true) {
        cout << "Enter N nodes: " << endl;
        id = enterString();
        if(isOnlyInt(id) && stoi(id) <= rows) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    string column;
    while(true) {
        cout << "1)sold" << endl;
        cout << "2)purchased" << endl;
        cout << "3)client" << endl;
        cout << "4)cashier" << endl;
        cout << "5)rate_sold" << endl;
        cout << "6)rate_purchased" << endl;
        cout << "7)date" << endl;
        cout << "8)time" << endl;
        cout << "9)sum_sold" << endl;
        cout << "10)sum_purchased" << endl;
        cout << "Enter column: " << endl;
        column = enterString();
        if(stoi(column) >= 1 && stoi(column) <= 10 && isOnlyInt(column)) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    int columnInt = stoi(column);
    string columnName;
    switch(columnInt) {
    case 1:
        columnName = "id_currency_sold";
        break;
    case 2:
        columnName = "id_currency_purchased";
        break;
    case 3:
        columnName = "id_client";
        break;
    case 4:
        columnName = "id_cashier";
        break;
    case 5:
        columnName = "id_rate_sold";
        break;
    case 6:
        columnName = "id_rate_purchased";
        break;
    case 7:
        columnName = "date_of_transaction";
        break;
    case 8:
        columnName = "time_of_transaction";
        break;
    case 9:
        columnName = "sum_currency_sold";
        break;
    case 10:
        columnName = "sum_currency_purchased";
        break;
    }

    string data;
    bool checkRatesSold = false;
    bool checkRatesPurchased = false;
    while(true) {
        if(stoi(column) == 1) {
            cout << "Enter N currencies sold: " << endl;
            data = enterString();
            if(stoi(data) > 0 && stoi(data) <= rowsCurrencies && isOnlyInt(data)) {
                bool check = false;
                map<int, Currencies*> tempMap2;
                for(int i = 0; i < cashCurrencies.getSize(); i++) {
                    tempMap2 = cashCurrencies.getElementDataById(i);
                    if (tempMap2.find(stoi(data)) != tempMap2.end()) {
                        data = cashCurrencies.getElementDataById(i).at(stoi(data))->getId();
                        check = true;
                        break;
                    }

                }

                if(!check) {
                    map<int, Currencies*> mapCurrencies;
                    currenciesGateway.loadRangeData(mapCurrencies, stoi(data), stoi(data));
                    data = mapCurrencies.at(stoi(data))->getId();
                }
                break;
            }
        }

        if(stoi(column) == 2) {
            cout << "Enter N currencies purchased: " << endl;
            data = enterString();
            if(stoi(data) > 0 && stoi(data) <= rowsCurrencies && isOnlyInt(data)) {
                bool check = false;
                map<int, Currencies*> tempMap2;
                for(int i = 0; i < cashCurrencies.getSize(); i++) {
                    tempMap2 = cashCurrencies.getElementDataById(i);
                    if (tempMap2.find(stoi(data)) != tempMap2.end()) {
                        data = cashCurrencies.getElementDataById(i).at(stoi(data))->getId();
                        check = true;
                        break;
                    }

                }

                if(!check) {
                    map<int, Currencies*> mapCurrencies;
                    currenciesGateway.loadRangeData(mapCurrencies, stoi(data), stoi(data));
                    data = mapCurrencies.at(stoi(data))->getId();
                }
                break;
            }
        }

        if(stoi(column) == 3) {
            cout << "Enter N client: " << endl;
            data = enterString();
            if(stoi(data) > 0 && stoi(data) <= rowsClients && isOnlyInt(data)) {
                bool check = false;
                map<int, Clients*> tempMap2;
                for(int i = 0; i < cashClients.getSize(); i++) {
                    tempMap2 = cashClients.getElementDataById(i);
                    if (tempMap2.find(stoi(data)) != tempMap2.end()) {
                        data = cashClients.getElementDataById(i).at(stoi(data))->getId();
                        check = true;
                        break;
                    }

                }

                if(!check) {
                    map<int, Clients*> mapClients;
                    clientsGateway.loadRangeData(mapClients, stoi(data), stoi(data));
                    data = mapClients.at(stoi(data))->getId();
                }
                break;
            }
        }

        if(stoi(column) == 4) {
            cout << "Enter N cashier: " << endl;
            data = enterString();
            if(stoi(data) > 0 && stoi(data) <= rowsCashiers && isOnlyInt(data)) {
                bool check = false;
                map<int, Cashiers*> tempMap2;
                for(int i = 0; i < cashCashiers.getSize(); i++) {
                    tempMap2 = cashCashiers.getElementDataById(i);
                    if (tempMap2.find(stoi(data)) != tempMap2.end()) {
                        data = cashCashiers.getElementDataById(i).at(stoi(data))->getId();
                        check = true;
                        break;
                    }

                }

                if(!check) {
                    map<int, Cashiers*> mapCashiers;
                    cashiersGateway.loadRangeData(mapCashiers, stoi(data), stoi(data));
                    data = mapCashiers.at(stoi(data))->getId();
                }
                break;
            }
        }

        if(stoi(column) == 5) {
            cout << "Enter N rate sold: " << endl;
            data = enterString();
            if(stoi(data) > 0 && stoi(data) <= rowsRates && isOnlyInt(data)) {
                bool check = false;
                map<int, Rates*> tempMap2;
                map<int, Transactions*> mapTransactions;
                transactionsGateway.loadRangeData(mapTransactions, cashClients, cashCashiers, cashCurrencies, cashRates, stoi(id), stoi(id));
                for(int i = 0; i < cashRates.getSize(); i++) {
                    tempMap2 = cashRates.getElementDataById(i);
                    if (tempMap2.find(stoi(data)) != tempMap2.end()) {
                        if(stoi(mapTransactions.at(stoi(id))->getCurrencySold().at(1)->getId()) == stoi(cashRates.getElementDataById(i).at(stoi(data))->getCurrencySold().at(1)->getId())) {
                            checkRatesSold = true;
                            checkRatesPurchased = true;
                        }
                        data = cashRates.getElementDataById(i).at(stoi(data))->getId();
                        check = true;
                        break;
                    }

                }

                if(!check) {
                    map<int, Rates*> mapRates;
                    ratesGateway.loadRangeData(mapRates, cashCurrencies, stoi(data), stoi(data));
                    if(stoi(mapTransactions.at(stoi(id))->getCurrencySold().at(1)->getId()) == stoi(mapRates.at(stoi(data))->getCurrencySold().at(1)->getId())) {
                        checkRatesSold = true;
                        checkRatesPurchased = true;
                    }
                    data = mapRates.at(stoi(data))->getId();
                }
                break;
            }
        }

        if(stoi(column) == 6) {
            cout << "Enter N rate purchased: " << endl;
            data = enterString();
            if(stoi(data) > 0 && stoi(data) <= rowsRates && isOnlyInt(data)) {
                bool check = false;
                map<int, Rates*> tempMap2;
                map<int, Transactions*> mapTransactions;
                transactionsGateway.loadRangeData(mapTransactions, cashClients, cashCashiers, cashCurrencies, cashRates, stoi(id), stoi(id));
                for(int i = 0; i < cashRates.getSize(); i++) {
                    tempMap2 = cashRates.getElementDataById(i);
                    if (tempMap2.find(stoi(data)) != tempMap2.end()) {
                        if(stoi(mapTransactions.at(stoi(id))->getCurrencyPurchased().at(1)->getId()) == stoi(cashRates.getElementDataById(i).at(stoi(data))->getCurrencyPurchased().at(1)->getId())) {
                            checkRatesSold = true;
                            checkRatesPurchased = true;
                        }
                        data = cashRates.getElementDataById(i).at(stoi(data))->getId();
                        check = true;
                        break;
                    }

                }

                if(!check) {
                    map<int, Rates*> mapRates;
                    ratesGateway.loadRangeData(mapRates, cashCurrencies, stoi(data), stoi(data));
                    if(stoi(mapTransactions.at(stoi(id))->getCurrencyPurchased().at(1)->getId()) == stoi(mapRates.at(stoi(data))->getCurrencyPurchased().at(1)->getId())) {
                        checkRatesSold = true;
                        checkRatesPurchased = true;
                    }
                    data = mapRates.at(stoi(data))->getId();
                }
                break;
            }
        }

        if(stoi(column) == 7) {
            cout << "Enter date: " << endl;
            data = enterString();
            if(isDate(data)) {
                break;
            }
        }

        if(stoi(column) == 8) {
            cout << "Enter time: " << endl;
            data = enterString();
            if(isTime(data)) {
                break;
            }
        }

        if(stoi(column) == 9) {
            cout << "Enter sum sold: " << endl;
            data = enterString();
            if(isOnlyIntAndPoint(data) && data.size()> 0 && data.size() < 10) {
                break;
            }
        }

        if(stoi(column) == 10) {
            cout << "Enter sum purchased: " << endl;
            data = enterString();
            if(isOnlyIntAndPoint(data) && data.size()> 0 && data.size() < 10) {
                break;
            }
        }

        cout << "Incorrect value!" << endl;
    }

    if(!checkRatesSold || !checkRatesPurchased) {
        cout << "Error! The exchange rate does not match the currency" << endl;
    } else {
    bool checkCash = false;
    for(int i = 0; i < cashTransactions.getSize(); i++) {
        tempMap = cashTransactions.getElementDataById(i);
        if (tempMap.find(stoi(id)) != tempMap.end()) {
            checkCash = true;
            Transactions *tempTransactions = tempMap.at(stoi(id));
            switch(columnInt) {
            case 1: {
                bool check2 = false;
                Currencies *currenciesSold;
                map<int, Currencies*> currencySold;
                for(int k = 0; k < cashCurrencies.getSize(); k++) {
                    map<int, Currencies*> tempMap = cashCurrencies.getElementDataById(k);
                    for (map<int, Currencies*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                        if(stoi(it->second->getId()) == stoi(data)) {
                            currenciesSold = cashCurrencies.getElementDataById(k).at(it->first);
                            check2 = true;
                            break;
                        }
                    }
                }

                if(!check2) {
                    currenciesSold = new Currencies();
                    currenciesGateway.loadDataById(currenciesSold, stoi(data));
                }
                currencySold.insert(make_pair(1, currenciesSold));
                tempTransactions->setCurrencySold(currencySold);
                break;
            }
            case 2: {
                bool check2 = false;
                Currencies *currenciesPurchased;
                map<int, Currencies*> currencyPurchased;
                for(int k = 0; k < cashCurrencies.getSize(); k++) {
                    map<int, Currencies*> tempMap = cashCurrencies.getElementDataById(k);
                    for (map<int, Currencies*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                        if(stoi(it->second->getId()) == stoi(data)) {
                            currenciesPurchased = cashCurrencies.getElementDataById(k).at(it->first);
                            check2 = true;
                            break;
                        }
                    }
                }

                if(!check2) {
                    currenciesPurchased = new Currencies();
                    currenciesGateway.loadDataById(currenciesPurchased, stoi(data));
                }

                currencyPurchased.insert(make_pair(1, currenciesPurchased));
                tempTransactions->setCurrencyPurchased(currencyPurchased);
                break;
            }
            case 3: {
                bool check2 = false;
                Clients *clients;
                map<int, Clients*> clientsMap;
                for(int k = 0; k < cashClients.getSize(); k++) {
                    map<int, Clients*> tempMap = cashClients.getElementDataById(k);
                    for (map<int, Clients*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                        if(stoi(it->second->getId()) == stoi(data)) {
                            clients = cashClients.getElementDataById(k).at(it->first);
                            check2 = true;
                            break;
                        }
                    }
                }

                if(!check2) {
                    clients = new Clients();
                    clientsGateway.loadDataById(clients, stoi(data));
                }

                clientsMap.insert(make_pair(1, clients));
                tempTransactions->setClient(clientsMap);
                break;
            }
            case 4: {
                bool check2 = false;

                Cashiers *cashiers;
                map<int, Cashiers*> cashiersMap;
                for(int k = 0; k < cashCashiers.getSize(); k++) {
                    map<int, Cashiers*> tempMap = cashCashiers.getElementDataById(k);
                    for (map<int, Cashiers*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                        if(stoi(it->second->getId()) == stoi(data)) {
                            cashiers = cashCashiers.getElementDataById(k).at(it->first);
                            check2 = true;
                            break;
                        }
                    }
                }

                if(!check2) {
                    cashiers = new Cashiers();
                    cashiersGateway.loadDataById(cashiers, stoi(data));
                }

                cashiersMap.insert(make_pair(1, cashiers));
                tempTransactions->setCashier(cashiersMap);
                break;
            }
            case 5 : {
                bool check2 = false;
                Rates *rateSold;
                map<int, Rates*> ratesMap;
                for(int k = 0; k < cashRates.getSize(); k++) {
                    map<int, Rates*> tempMap = cashRates.getElementDataById(k);
                    for (map<int, Rates*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                        if(stoi(it->second->getId()) == stoi(data)) {
                            rateSold = cashRates.getElementDataById(k).at(it->first);
                            check2 = true;
                            break;
                        }
                    }
                }

                if(!check2) {
                    rateSold = new Rates();
                    ratesGateway.loadDataById(rateSold, cashCurrencies, stoi(data));
                }

                ratesMap.insert(make_pair(1, rateSold));
                tempTransactions->setRateSold(ratesMap);
                break;
            }
            case 6 : {
                bool check2 = false;
                Rates *ratePurchased;
                map<int, Rates*> rates2Map;
                for(int k = 0; k < cashRates.getSize(); k++) {
                    map<int, Rates*> tempMap = cashRates.getElementDataById(k);
                    for (map<int, Rates*>::iterator it = tempMap.begin(); it != tempMap.end(); ++it) {
                        if(stoi(it->second->getId()) == stoi(data)) {
                            ratePurchased = cashRates.getElementDataById(k).at(it->first);
                            check2 = true;
                            break;
                        }
                    }
                }

                if(!check2) {
                    ratePurchased = new Rates();
                    ratesGateway.loadDataById(ratePurchased, cashCurrencies, stoi(data));
                }

                rates2Map.insert(make_pair(1, ratePurchased));
                tempTransactions->setRatePurchased(rates2Map);
                break;
            }
            case 7 : {
                tempTransactions->setDate(data);
                break;
            }
            case 8 : {
                tempTransactions->setTime(data);
                break;
            }
            case 9 : {
                tempTransactions->setSumCurrencySold(data);
                break;
            }
            case 10 : {
                tempTransactions->setSumCurrencyPurchased(data);
                break;
            }
            }
            tempMap[stoi(id)] = tempTransactions;
            cashTransactions.setElementDataById(i, tempMap);
            break;
        }
    }
    if(!checkCash) {
        transactionsGateway.loadRangeData(tempMap, cashClients, cashCashiers, cashCurrencies, cashRates, stoi(id), stoi(id));
    }
    transactionsGateway.update(stoi(tempMap.at(stoi(id))->getId()), columnName, data);
    cout << "Node updated!" << endl;
    }
}

void UserAction::deleteTransactions() {
    int rows = transactionsGateway.getFullCountRows();
    string id;
    while(true) {
        cout << "Enter N nodes: " << endl;
        id = enterString();
        if(isOnlyInt(id) && stoi(id) <= rows) {
            break;
        } else {
            cout << "Incorrect value!" << endl;
        }
    }
    map<int, Transactions*> tempMap;
    int idDel;
    bool checkCash = false;
    for(int i = 0; i < cashTransactions.getSize(); i++) {
        tempMap = cashTransactions.getElementDataById(i);
        if (tempMap.find(stoi(id)) != tempMap.end()) {
            checkCash = true;
            idDel = i;
            break;
        }
    }
    if(!checkCash) {
        idDel = 0;
        transactionsGateway.loadRangeData(tempMap, cashClients, cashCashiers, cashCurrencies, cashRates, stoi(id), stoi(id));
    }

    int tempId;
        for(int i = idDel, tempId = stoi(id); i < cashTransactions.getSize();) {
            map<int, Transactions*> tempMap1;
            tempMap1 = cashTransactions.getElementDataById(i);
            if (!(tempMap1.find(tempId) != tempMap1.end())) {
                tempId++;
                continue;
            }
            for(int j = 0; j < tempMap1.size(); j++) {
                if (!(tempMap1.find(tempId+1) != tempMap1.end())) {
                    break;
                }
                tempMap1[tempId] = tempMap1[tempId+1];
                tempId++;
            }

            if(i+1 != cashTransactions.getSize()) {
                map<int, Transactions*> tempMap2;
                tempMap2 = cashTransactions.getElementDataById(i+1);
                tempMap1[tempId] = tempMap2[tempId+1];
                tempId++;
            } else {
                if (tempMap1.find(rows) != tempMap1.end()) {
                    tempMap1.erase(tempId);
                } else {
                    map<int, Transactions*> tempMap2;
                    transactionsGateway.loadRangeData(tempMap2, cashClients, cashCashiers, cashCurrencies, cashRates, tempId+1, tempId+1);
                    tempMap1[tempId] = tempMap2[tempId+1];
                }
            }
            if(tempMap1.empty()) {
                cashTransactions.Prev();
                cashTransactions.delToEnd();
                pageTransactions--;
            } else {
                cashTransactions.setElementDataById(i, tempMap1);
            }
            i++;
        }
    transactionsGateway.del(stoi(tempMap.at(stoi(id))->getId()));
    cout << "Node deleted!" << endl;
}

void UserAction::clearCashTransactions() {
    pageTransactions = 1;
    cashTransactions.clear();
}

void UserAction::loadCashTransactions() {
    pageTransactions = 1;
    map<int, Transactions*> mapTransactions;
    transactionsGateway.loadRangeData(mapTransactions, cashClients, cashCashiers, cashCurrencies, cashRates, 1, countObjectOnPage);
    cashTransactions.addToEnd(mapTransactions);
}

string UserAction::enterString() {
	string line;
	while (true) {
		cout << ">> ";
		cin >> line;
		bool error = false;

		if (!error && (cin.peek() == '\n')) {
			break;
		}
		else {
			cout << "Incorrect value!" << endl;
			cin.clear();
			while (cin.get() != '\n') {}
		}
		cout << endl;
	}
	return line;
}

int UserAction::enterNumber(int min, int max) {
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

bool UserAction::isOnlyInt(string str) {
    bool result = true;
	for(int i = 0; i < str.size(); i++) {
        if(!((int)str[i] >= 48 && (int)str[i] <= 57)) {
            result = false;
            break;
        }
	}
	return result;
}

bool UserAction::isOnlyIntAndPoint(string str) {
    bool result = true;
	for(int i = 0; i < str.size(); i++) {
        if(!(((int)str[i] >= 48 && (int)str[i] <= 57) || (int)str[i] == 46)) {
            result = false;
            break;
        }
	}
	return result;
}

bool UserAction::isOnlyString(string str) {
	bool result = true;
	for(int i = 0; i < str.size(); i++) {
        if(!((int)str[i] >= 65 && (int)str[i] <= 122)) {
            result = false;
            break;
        }
	}
	return result;
}

int UserAction::getRandomInt(int min, int max) {
	return rand() * (max - min + 1) + min;
}

string UserAction::getDate() {
	time_t t = time(nullptr);
    tm* now = localtime(&t);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);
    return buffer;
}

string UserAction::getTime() {
	time_t t = time(nullptr);
    tm* now = localtime(&t);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%X", now);
    return buffer;
}

bool UserAction::isDate(string date) {
    bool result = true;
    if(date.size() != 10) {
        result = false;
    }
	for(int i = 0; i < date.size(); i++) {
        if(!(((int)date[i] >= 48 && (int)date[i] <= 57) || (int)date[i] == 45)) {
            result = false;
            break;
        }
	}
	if((int)date[4] != 45 || (int)date[7] != 45) {
        result = false;
	}
	if((int)date[5] >= 48 || (int)date[5] <= 49) {
        result = false;
	}
	if((int)date[8] >= 48 || (int)date[8] <= 51) {
        result = false;
	}
	return result;
}

bool UserAction::isTime(string time) {
    bool result = true;
    if(time.size() != 8) {
        result = false;
    }
	for(int i = 0; i < time.size(); i++) {
        if(!(((int)time[i] >= 48 && (int)time[i] <= 57) || (int)time[i] == 58)) {
            result = false;
            break;
        }
	}
	if((int)time[2] != 58 || (int)time[5] != 58) {
        result = false;
	}
	if((int)time[0] >= 48 || (int)time[0] <=  50) {
        result = false;
	}
	if((int)time[3] >=  48 || (int)time[3] <=  54) {
        result = false;
	}
	if((int)time[6] >=  48 || (int)time[6] <=  54) {
        result = false;
	}
	return result;
}
