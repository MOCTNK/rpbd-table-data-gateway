#include "Currencies.h"

Currencies::Currencies()
{

}

Currencies::~Currencies()
{

}

void Currencies::setId(string id) {
    this->id = id;
}

void Currencies::setCode(string code) {
    this->code = code;
}

void Currencies::setName(string name) {
    this->name = name;
}

string Currencies::getId() {
    return id;
}

string Currencies::getCode() {
    return code;
}

string Currencies::getName() {
    return name;
}

Currencies& Currencies::operator=(Currencies& other) {
    setId(other.getId());
    setCode(other.getCode());
    setName(other.getName());
    return *this;
}
