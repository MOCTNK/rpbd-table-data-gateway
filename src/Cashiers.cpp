#include "Cashiers.h"

Cashiers::Cashiers()
{

}

Cashiers::~Cashiers()
{

}

void Cashiers::setId(string id) {
    this->id = id;
}

void Cashiers::setName(string name) {
    this->name = name;
}

void Cashiers::setSurname(string surname) {
    this->surname = surname;
}

void Cashiers::setPatronymic(string patronymic) {
    this->patronymic = patronymic;
}

string Cashiers::getId() {
    return id;
}

string Cashiers::getName() {
    return name;
}

string Cashiers::getSurname() {
    return surname;
}

string Cashiers::getPatronymic() {
    return patronymic;
}

Cashiers& Cashiers::operator=(Cashiers& other) {
    setId(other.getId());
    setName(other.getName());
    setSurname(other.getSurname());
    setPatronymic(other.getPatronymic());
    return *this;
}
