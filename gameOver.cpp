
#include <iostream>
#include "gameOver.h"

bool Monopoly::gameOver(int countTurns, std::vector<Player> &players, int numPlayers, int turnLimit) {
    int counter = 0;
    if (countTurns == turnLimit) {
        return true;
    }
    for (int i = 0; i < numPlayers; i++) {
        if (players.at(i).getInGame()) {
            counter++;
        }
    }
    return counter == 1;
}