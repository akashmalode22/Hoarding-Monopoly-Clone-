#include <iostream>
#include "Board.h"

Monopoly::Board::Board(int data1, int data2) : playerTurn(data1), countTurns(data2) {}

void Monopoly::Board::setPlayerTurn(int data) {
    playerTurn = data;
}

void Monopoly::Board::setCountTurns(int data) {
    countTurns = data;
}

int Monopoly::Board::getPlayerTurn() {
    return playerTurn;
}

int Monopoly::Board::getCountTurns() {
    return countTurns;
}

void Monopoly::Board::displayBoard(std::vector<Player> &players, int numPlayers, std::vector<Property> &properties,
                                   int numProperties) {
    int countPlayers = 0;
    std::cout << "Space Number | Space Name | Owner | Upgrades | Players" << std::endl;
    for (int i = 0; i < numProperties; i++) {
        std::cout << properties.at(i).getPropertyNumber() << "\t\t\t | " << properties.at(i).getName() << "\t\t| "
                  << properties.at(i).getPlayerOwner() << "\t| ";
        if (properties.at(i).getNumHotels() != 1) {
            for (int l = 0; l < properties.at(i).getNumHouses(); l++) {
                std::cout << "h";
            }
        } else if (properties.at(i).getNumHotels() == 1) {
            std::cout << "H";
        }
        std::cout << " | ";
        for (int k = 0; k < numPlayers; k++) {
            if (players.at(k).getPosition() == i && players.at(k).getInGame() == true) {
                countPlayers++;
            }
        }
        for (int j = 0; j < numPlayers; j++) {

            if (players.at(j).getPosition() == i && players.at(j).getInGame()) {
                countPlayers--;
                if (countPlayers == 0) {
                    std::cout << "[" << players.at(j).getName() << " : " << "$" << players.at(j).getCash() << "] ";
                } else {
                    std::cout << "[" << players.at(j).getName() << " : " << "$" << players.at(j).getCash() << "], ";
                }

            }

        }
        std::cout << std::endl;
    }
}

void Monopoly::Board::changeTurn(Board &board, int &numPlayers, std::vector<Player> &players) {
    int counter = 0;
    int flag = -1;
    int flag2 = -1;
    if (board.getPlayerTurn() == numPlayers - 1) {
        while (flag != 0) {
            if (players.at(counter).getInGame() == false) {
                counter++;
            } else {
                flag = 0;
                board.setPlayerTurn(counter);
            }
        }
    } else {
        while (flag2 != 0) {
            if (board.getPlayerTurn() == numPlayers - 1) {
                board.setPlayerTurn(0);
                break;
            }
            if (players.at(board.getPlayerTurn() + 1).getInGame() == false) {
                board.setPlayerTurn(board.getPlayerTurn() + 1);
            } else {
                board.setPlayerTurn(board.getPlayerTurn() + 1);
                flag2 = 0;
            }
        }
    }
}

void Monopoly::Board::declareWinners(std::vector<Player> &players, int numPlayers) {
    std::cout << "The winners are" << std::endl;
    for (int i = 0; i < numPlayers; i++) {
        if (players.at(i).getInGame()) {
            std::cout << players.at(i).getName() << std::endl;
        }
    }
}