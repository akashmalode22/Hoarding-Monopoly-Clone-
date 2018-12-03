
#include "Rules.h"
#include "CSVReader.h"

void Monopoly::Rules::setNumPlayers(int data) {
    numPlayers = data;
}

void Monopoly::Rules::setEvenHouses(bool data) {
    evenHouses = data;
}

void Monopoly::Rules::setMoneyInParking(bool data) {
    moneyInParking = data;
}

void Monopoly::Rules::setAuctionProperty(bool data) {
    auctionProperty = data;
}

int Monopoly::Rules::getNumPlayers() {
    return numPlayers;
}

bool Monopoly::Rules::getEvenHouses() {
    return evenHouses;
}

bool Monopoly::Rules::getMoneyInParking() {
    return moneyInParking;
}

bool Monopoly::Rules::getAuctionProperty() {
    return auctionProperty;
}
