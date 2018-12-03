
#include <vector>
#include "Player.h"

#ifndef MONOPOLY_GAMEOVER_H
#define MONOPOLY_GAMEOVER_H

namespace Monopoly {
    bool gameOver(int countTurns, std::vector<Player> &players, int numPlayers, int turnLimit);
}

#endif //MONOPOLY_GAMEOVER_H
