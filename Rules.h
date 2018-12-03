
#ifndef MONOPOLY_RULES_H
#define MONOPOLY_RULES_H

#include <string>
#include <fstream>

namespace Monopoly {
    class Rules {
    private:
        int numPlayers;
        bool evenHouses;
        bool moneyInParking;
        bool auctionProperty;
        std::string fileName;
        std::ifstream file;
    public:

        void setNumPlayers(int data);

        void setEvenHouses(bool data);

        void setMoneyInParking(bool data);

        void setAuctionProperty(bool data);

        int getNumPlayers();

        bool getEvenHouses();

        bool getMoneyInParking();

        bool getAuctionProperty();
    };
}

#endif //MONOPOLY_RULES_H
