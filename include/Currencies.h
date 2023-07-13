#pragma once
#include <iostream>
#include "string.h"
#include "Object.h"
using namespace std;

class Currencies : public Object {
public:
    Currencies();
    ~Currencies();
    void setId(string id);
    void setCode(string code);
    void setName(string name);
    string getId();
    string getCode();
    string getName();
    Currencies& operator=(Currencies& other);
private:
    string id;
    string code;
    string name;
    int columns = 3;
};
