#include "Transactions.h"

Transactions::Transactions()
{

}

Transactions::~Transactions()
{

}

void Transactions::setId(string id) {
    this->id = id;
}

void Transactions::setCurrencySold(map<int, Currencies*> currencySold) {
    this->currencySold = currencySold;
}

void Transactions::setCurrencyPurchased(map<int, Currencies*> currencyPurchased) {
    this->currencyPurchased = currencyPurchased;
}

void Transactions::setClient(map<int, Clients*> client) {
    this->client = client;
}

void Transactions::setCashier(map<int, Cashiers*> cashier) {
    this->cashier = cashier;
}

void Transactions::setRateSold(map<int, Rates*> rateSold) {
    this->rateSold = rateSold;
}

void Transactions::setRatePurchased(map<int, Rates*> ratePurchased) {
    this->ratePurchased = ratePurchased;
}

void Transactions::setDate(string date) {
    this->date = date;
}

void Transactions::setTime(string time) {
    this->time = time;
}

void Transactions::setSumCurrencySold(string sumCurrencySold) {
    this->sumCurrencySold = sumCurrencySold;
}

void Transactions::setSumCurrencyPurchased(string sumCurrencyPurchased) {
    this->sumCurrencyPurchased = sumCurrencyPurchased;
}

string Transactions::getId() {
    return id;
}

map<int, Currencies*> Transactions::getCurrencySold() {
    return currencySold;
}

map<int, Currencies*> Transactions::getCurrencyPurchased() {
    return currencyPurchased;
}

map<int, Clients*> Transactions::getClient() {
    return client;
}

map<int, Cashiers*> Transactions::getCashier() {
    return cashier;
}

map<int, Rates*> Transactions::getRateSold() {
    return rateSold;
}

map<int, Rates*> Transactions::getRatePurchased() {
    return ratePurchased;
}

string Transactions::getDate() {
    return date;
}

string Transactions::getTime() {
    return time;
}

string Transactions::getSumCurrencySold() {
    return sumCurrencySold;
}

string Transactions::getSumCurrencyPurchased() {
    return sumCurrencyPurchased;
}

Transactions& Transactions::operator=(Transactions& other) {
    setId(other.getId());
    setCurrencySold(other.getCurrencySold());
    setCurrencyPurchased(other.getCurrencyPurchased());
    setClient(other.getClient());
    setCashier(other.getCashier());
    setRateSold(other.getRateSold());
    setRatePurchased(other.getRatePurchased());
    setDate(other.getDate());
    setTime(other.getTime());
    setSumCurrencySold(other.getSumCurrencySold());
    setSumCurrencyPurchased(other.getSumCurrencyPurchased());
    return *this;
}
