
#include "Auction.h"
#include <utility>

bool Monopoly::Auction::getPlayerInAuction() {
    return playerInAuction;
}

std::string Monopoly::Auction::getName() {
    return name;
}

void Monopoly::Auction::setPlayerInAuction(bool data) {
    playerInAuction = data;
}

void Monopoly::Auction::setName(std::string data) {
    name = std::move(data);
}

Monopoly::Auction::Auction() {
    name = " ";
}