
#include "Player.h"
#include <iostream>

void Monopoly::Player::setCash(int data) {
    cash = data;
}

int Monopoly::Player::getCash() {
    return cash;
}

void Monopoly::Player::setName(const std::string &data) {
    name = data;
}

std::string Monopoly::Player::getName() {
    return name;
}

void Monopoly::Player::setID(int data) {
    playerID = data;
}

int Monopoly::Player::getID() {
    return playerID;
}

void Monopoly::Player::setPosition(int data) {
    position = data;
}

int Monopoly::Player::getPosition() {
    return position;
}

void Monopoly::Player::setInGame(bool data) {
    inGame = data;
}

bool Monopoly::Player::getInGame() {
    return inGame;
}

int Monopoly::Player::getSetID() {
    return playerID;
}

void Monopoly::setPlayerData(std::vector<Player> &players, Rules &rules, Gamestate &gamestate, int &numPlayers) {
    std::cout << "Enter how many players will be playing: ";
    std::cin >> numPlayers;
    rules.setNumPlayers(numPlayers);
    Player tempPlayer;

    for (int i = 1; i < numPlayers + 1; i++) {
        std::string name;
        tempPlayer.setID(i);
        std::cout << "Enter the name of player " << i << ": ";
        std::cin >> name;
        tempPlayer.setName(name);
        tempPlayer.setPosition(0);
        tempPlayer.setCash(gamestate.getStartCash());
        tempPlayer.setInGame(true);
        players.emplace_back(tempPlayer);
    }
}