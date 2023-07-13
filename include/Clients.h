#pragma once
#include <iostream>
#include "string.h"
#include "Object.h"
using namespace std;

class Clients : public Object {
public:
    Clients();
    ~Clients();
    void setId(string id);
    void setName(string name);
    void setSurname(string surname);
    void setPatronymic(string patronymic);
    void setPassportSeries(string passportSeries);
    void setPassportNumber(string passportNumber);
    string getId();
    string getName();
    string getSurname();
    string getPatronymic();
    string getPassportSeries();
    string getPassportNumber();
    Clients& operator=(Clients& other);
private:
    string id;
    string name;
    string surname;
    string patronymic;
    string passportSeries;
    string passportNumber;
    int columns = 6;
};
