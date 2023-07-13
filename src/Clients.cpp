#include "Clients.h"

Clients::Clients()
{

}

Clients::~Clients()
{

}

void Clients::setId(string id) {
    this->id = id;
}

void Clients::setName(string name) {
    this->name = name;
}

void Clients::setSurname(string surname) {
    this->surname = surname;
}

void Clients::setPatronymic(string patronymic) {
    this->patronymic = patronymic;
}

void Clients::setPassportSeries(string passportSeries) {
    this->passportSeries = passportSeries;
}

void Clients::setPassportNumber(string passportNumber) {
    this->passportNumber = passportNumber;
}

string Clients::getId() {
    return id;
}

string Clients::getName() {
    return name;
}

string Clients::getSurname() {
    return surname;
}

string Clients::getPatronymic() {
    return patronymic;
}

string Clients::getPassportSeries() {
    return passportSeries;
}

string Clients::getPassportNumber() {
    return passportNumber;
}

Clients& Clients::operator=(Clients& other) {
    setId(other.getId());
    setName(other.getName());
    setSurname(other.getSurname());
    setPatronymic(other.getPatronymic());
    setPassportSeries(other.getPassportSeries());
    setPassportNumber(other.getPassportNumber());
    return *this;
}
