
#include <iostream>
#include "Gamestate.h"
#include "CSVReader.h"
#include "Rules.h"

void Monopoly::Gamestate::setStartCash(int data) {
    startCash = data;
}

int Monopoly::Gamestate::getStartCash() {
    return startCash;
}

void Monopoly::Gamestate::setTurnLimit(int data) {
    turnLimit = data;
}

int Monopoly::Gamestate::getTurnLimit() {
    return turnLimit;
}

void Monopoly::Gamestate::setNumPlayersLeftToEndGame(int data) {
    numPlayersLeftToEndGame = data;
}

int Monopoly::Gamestate::getNumPlayersLeftToEndGame() {
    return numPlayersLeftToEndGame;
}

void Monopoly::Gamestate::setPropSetMultiplier(int data) {
    propSetMultiplier = data;
}

int Monopoly::Gamestate::getPropSetMultiplier() {
    return propSetMultiplier;
}

void Monopoly::Gamestate::setNumHousesBeforeHotels(int data) {
    numHousesBeforeHotels = data;
}

int Monopoly::Gamestate::getNumHousesBeforeHotels() {
    return numHousesBeforeHotels;
}

void Monopoly::Gamestate::setSalaryMultiplier(int data) {
    salaryMultiplier = data;
}

int Monopoly::Gamestate::getSalaryMultiplier() {
    return salaryMultiplier;
}

Monopoly::Gamestate::Gamestate(const std::string &data) {
    fileName = data;
    file.open(data);
}

void Monopoly::Gamestate::setMaxDoubleReRolls(int data) {
    maxDoubleReRolls = data;
}

int Monopoly::Gamestate::getMaxDoubleReRolls() {
    return maxDoubleReRolls;
}

void Monopoly::getGamestate(Gamestate &gamestate, Rules &rules) {
    std::string junk;
    int data;
    std::string strdata;

    std::getline(gamestate.file, junk, ':');
    gamestate.file >> data;
    gamestate.setStartCash(data);

    std::getline(gamestate.file, junk, ':');
    gamestate.file >> data;
    gamestate.setTurnLimit(data);

    std::getline(gamestate.file, junk, ':');
    gamestate.file >> data;
    gamestate.setNumPlayersLeftToEndGame(data);

    std::getline(gamestate.file, junk, ':');
    gamestate.file >> data;
    gamestate.setPropSetMultiplier(data);

    std::getline(gamestate.file, junk, ':');
    gamestate.file >> data;

    gamestate.setNumHousesBeforeHotels(data);

    std::getline(gamestate.file, junk, ':');
    gamestate.file >> strdata;
    if (strdata == "Yes")
        rules.setEvenHouses(true);
    else if (strdata == "No")
        rules.setEvenHouses(false);

    std::getline(gamestate.file, junk, ':');
    gamestate.file >> strdata;
    if (strdata == "Yes")
        rules.setMoneyInParking(true);
    else if (strdata == "No")
        rules.setMoneyInParking(false);

    std::getline(gamestate.file, junk, ':');
    gamestate.file >> strdata;
    if (strdata == "Yes")
        rules.setAuctionProperty(true);
    else if (strdata == "No")
        rules.setAuctionProperty(false);

    std::getline(gamestate.file, junk, ':');
    gamestate.file >> data;
    gamestate.setSalaryMultiplier(data);

    std::getline(gamestate.file, junk, ':');
    gamestate.file >> data;
    gamestate.setMaxDoubleReRolls(data);
}
