
#ifndef MONOPOLY_C_AUCTION_H
#define MONOPOLY_C_AUCTION_H

#include <string>

namespace Monopoly {
    class Auction {
    private:
        bool playerInAuction;
        std::string name;
    public:
        Auction();

        bool getPlayerInAuction();

        std::string getName();

        void setPlayerInAuction(bool data);

        void setName(std::string data);
    };
}
#endif //MONOPOLY_C_AUCTION_H
