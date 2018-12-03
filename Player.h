
#ifndef MONOPOLY_PLAYER_H
#define MONOPOLY_PLAYER_H

#include <vector>
#include <string>
#include "Gamestate.h"
#include "Rules.h"

namespace Monopoly {
    class Player {
    private:
        std::string name;
        int playerID;
        int cash;
        int position;
        bool inGame;
    public:

        void setName(const std::string &data);

        std::string getName();

        void setID(int data);

        int getSetID();

        int getID();

        void setPosition(int data);

        int getPosition();

        void setCash(int data);

        int getCash();

        void setInGame(bool data);

        bool getInGame();

    };

    void setPlayerData(std::vector<Player> &players, Rules &rules, Gamestate &gamestate, int &numPlayers);
}

#endif //MONOPOLY_PLAYER_H
