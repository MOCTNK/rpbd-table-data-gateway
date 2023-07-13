#pragma once
#include <iostream>
#include "Object.h"
#include "string.h"
#include "Object.h"
using namespace std;

class Cashiers : public Object {
public:
    Cashiers();
    ~Cashiers();
    void setId(string id);
    void setName(string name);
    void setSurname(string surname);
    void setPatronymic(string patronymic);
    string getId();
    string getName();
    string getSurname();
    string getPatronymic();
    void view();
    Cashiers& operator=(Cashiers& other);
private:
    string id;
    string name;
    string surname;
    string patronymic;
    int columns = 4;
};
