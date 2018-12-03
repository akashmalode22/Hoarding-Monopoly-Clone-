
#include <iostream>
#include <vector>
#include "Player.h"
#include "Rules.h"
#include "move.h"
#include "CSVReader.h"
#include "Property.h"
#include "Space.h"
#include "gameOver.h"
#include "Board.h"
#include "DiceRoller.h"

void entireProgram(int argc, char **argv) {
    int numPlayers;
    int counter = 0;
    int move;
    int numProperties;
    Monopoly::Rules rules;
    Monopoly::Board board(0, 0);
    Monopoly::Gamestate gamestate(argv[1]);
    Monopoly::Space space;
    Monopoly::getStart(argv[2], space);
    std::vector<Monopoly::Player> players;
    Monopoly::DiceRoller roller(argv[3]);
    Monopoly::getNumProperties(argv[2], numProperties);

    std::vector<Monopoly::Property> properties(static_cast<unsigned long>(numProperties));

    Monopoly::getGamestate(gamestate, rules);
    Monopoly::setProperty(properties, numProperties, argv[2]);
    Monopoly::setPlayerData(players, rules, gamestate, numPlayers);
    int c=0;
    while (!Monopoly::gameOver(board.getCountTurns(), players, numPlayers, gamestate.getTurnLimit())) {
        OUT:
        board.displayBoard(players, numPlayers, properties, numProperties);
        Monopoly::getMove(players, board, move);
        Monopoly::makeMove(players, board, move, argv[3], numProperties, gamestate, properties, rules, space,
                           numPlayers, roller);
        if (move == 1 && roller.getFlag() == 1 && counter != gamestate.getMaxDoubleReRolls()) {
            ++counter;
            goto OUT;
        }
        if (move == 2 || move == 3) {
            goto OUT;
        }
        board.changeTurn(board, numPlayers, players);
        board.setCountTurns(board.getCountTurns() + 1);
      counter = 0;
      c++;
    }

    board.displayBoard(players, numPlayers, properties, numProperties);
    board.declareWinners(players, numPlayers);
}


int main(int argc, char **argv) {
    entireProgram(argc, argv);
    return 0;
}