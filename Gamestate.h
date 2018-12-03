
#ifndef MONOPOLY_GAMESTATE_H
#define MONOPOLY_GAMESTATE_H

#include <string>
#include <fstream>
#include "Rules.h"

namespace Monopoly {
    class Gamestate {
    private:
        std::string fileName;
        int startCash;
        int turnLimit;
        int numPlayersLeftToEndGame;
        int propSetMultiplier;
        int numHousesBeforeHotels;
        int salaryMultiplier;
        int maxDoubleReRolls;
    public:
        explicit Gamestate(const std::string &data);

        std::ifstream file;

        void setMaxDoubleReRolls(int data);

        int getMaxDoubleReRolls();

        void setStartCash(int startCash);

        int getStartCash();

        void setTurnLimit(int turnLimit);

        int getTurnLimit();

        void setNumPlayersLeftToEndGame(int numPlayersLeftToEndGame);

        int getNumPlayersLeftToEndGame();

        void setPropSetMultiplier(int data);

        int getPropSetMultiplier();

        void setNumHousesBeforeHotels(int data);

        int getNumHousesBeforeHotels();

        void setSalaryMultiplier(int data);

        int getSalaryMultiplier();

    };

    void getGamestate(Gamestate &gamestate, Rules &rules);
}
#endif //MONOPOLY_GAMESTATE_H
