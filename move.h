
#include "Player.h"
#include "Property.h"
#include "Space.h"
#include "DiceRoller.h"
#include "Board.h"
#include "Gamestate.h"
#include <vector>

#ifndef MONOPOLY_MOVE_H
#define MONOPOLY_MOVE_H

namespace Monopoly {
    void getMove(std::vector<Player> &players, Board &board, int &move);

    void makeMove(std::vector<Player> &players, Board &board, int move, const std::string &fileName,
                  int &numProperties, Gamestate &gamestate, std::vector<Property> &properties, Rules &rules,
                  Space &space, int &numPlayers, DiceRoller &roller);

    void leaveGame(std::vector<Player> &players, Board &board, std::vector<Property> &properties, int numProperties);

    void performMove(std::vector<Player> &players, Board &board, const std::string &fileName,
                     int &numProperties, Gamestate &gamestate, std::vector<Property> &properties,
                     Rules &rules, Space &space, int &numPlayers, DiceRoller &roller);

    bool setOwned(std::vector<Player> &players, std::vector<Property> &properties, int &tempPosition,
                  Board &board, int &numProperties);

    void upgradeHouse(std::vector<Player> &players, Board &board, int &numPlayers, int &numProperties,
                      Gamestate &gamestate, std::vector<Property> &properties, Rules &rules, Space &space);

    void sellHouse(std::vector<Player> &players, Board &board, int &numPlayers, int &numProperties,
                   Gamestate &gamestate, std::vector<Property> &properties, Rules &rules, Space &space);

    bool allEven(std::vector<Property> &properties, int numProperties, int position);

    bool checkMaxHouses(std::vector<Property> &properties, int numProperties, int position);

    bool setHasHotel(std::vector<Property> &properties, int numProperties, int position);

    bool sellForDebt(std::vector<Property> &properties, int numProperties, Board &board, std::vector<Player> &players,
                     int tempPosition, int moneyOwed, Monopoly::Gamestate &gamestate);

    void startAuction(std::vector<Player> &players, Board &board, const std::string &fileName,
                      int &numProperties, Gamestate &gamestate, std::vector<Property> &properties, Rules &rules,
                      Space &space, int &numPlayers, DiceRoller &roller, int tempPosition);
}
#endif //MONOPOLY_MOVE_H
