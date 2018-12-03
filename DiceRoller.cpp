
#include "DiceRoller.h"
#include <fstream>
#include <sstream>

int Monopoly::DiceRoller::getRandomFromFile() {
    int num;
    std::string field;
    file >> field;
    num = stoi(field);
    return num;
}

Monopoly::DiceRoller::DiceRoller(const std::string &data) {
    fileName = data;
    file.open(data);
}

int Monopoly::DiceRoller::getFlag() {
    return flag;
}

void Monopoly::DiceRoller::setFlag(int data) {
    flag = data;
}
