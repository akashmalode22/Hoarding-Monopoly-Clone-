
#ifndef MONOPOLY_DICEROLLER_H
#define MONOPOLY_DICEROLLER_H

#include <iostream>
#include <string>
#include <fstream>

namespace Monopoly {

    class DiceRoller {
    private:
        int flag;
        std::string fileName;
        std::ifstream file;
    public:
        explicit DiceRoller(const std::string &data);

        int getFlag();

        void setFlag(int data);

        int getRandomFromFile();
    };
}


#endif //MONOPOLY_DICEROLLER_H
