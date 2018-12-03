
#ifndef MONOPOLY_BOARD_H
#define MONOPOLY_BOARD_H

#include "Player.h"
#include "Property.h"
#include <vector>
namespace Monopoly {

    class Board {
    private:
        int playerTurn;
        int countTurns;
    public:
        void setPlayerTurn(int data);

        void setCountTurns(int data);

        int getPlayerTurn();

        int getCountTurns();

        Board(int data1, int data2);

        void displayBoard(std::vector<Player> &players, int numPlayers, std::vector<Property> &properties,
                          int numProperties);

        void changeTurn(Board &board, int &numPlayers, std::vector<Player> &players);

        void declareWinners(std::vector<Player> &players, int numPlayers);

    };
}

#endif //MONOPOLY_BOARD_H
