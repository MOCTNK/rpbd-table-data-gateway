#include "Rates.h"

Rates::Rates()
{

}

Rates::~Rates()
{

}

void Rates::setId(string id) {
    this->id = id;
}

void Rates::setCurrencySold(map<int, Currencies*> currencySold) {
    this->currencySold = currencySold;
}

void Rates::setCurrencyPurchased(map<int, Currencies*> currencyPurchased) {
    this->currencyPurchased = currencyPurchased;
}

void Rates::setSaleRate(string saleRate) {
    this->saleRate = saleRate;
}

void Rates::setPurchaseRate(string purchaseRate) {
    this->purchaseRate = purchaseRate;
}

string Rates::getId() {
    return id;
}

map<int, Currencies*> Rates::getCurrencySold() {
    return currencySold;
}

map<int, Currencies*> Rates::getCurrencyPurchased() {
    return currencyPurchased;
}

string Rates::getSaleRate() {
    return saleRate;
}

string Rates::getPurchaseRate() {
    return purchaseRate;
}

Rates& Rates::operator=(Rates& other) {
    setId(other.getId());
    setCurrencySold(other.getCurrencySold());
    setCurrencyPurchased(other.getCurrencyPurchased());
    setSaleRate(other.getSaleRate());
    setPurchaseRate(other.getPurchaseRate());
    return *this;
}
