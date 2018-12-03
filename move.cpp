
#include "move.h"
#include <vector>
#include "Player.h"
#include <string>
#include <cmath>
#include "DiceRoller.h"
#include "Property.h"
#include "Space.h"
#include "Board.h"
#include "Auction.h"

bool Monopoly::allEven(std::vector<Property> &properties, int numProperties, int position) {
  int num = 0;
  int setID = properties.at(position).getSetID();
  for (int i = 1; i < numProperties; i++) {
    if (properties.at(i).getSetID() == setID) {
      if (properties.at(i).getNumHotels() == 1) {
        continue;
      }
      num = properties.at(i).getNumHouses();
      break;
    }
  }
  int flag = 0;
  for (int i = 1; i < numProperties; i++) {
    if (properties.at(i).getSetID() == setID) {
      if (properties.at(i).getNumHotels() == 1) {
        continue;
      }
      if (properties.at(i).getNumHouses() != num) {
        flag = 1;
      }
    }
  }
  return flag == 0;
}

bool Monopoly::checkMaxHouses(std::vector<Property> &properties, int numProperties, int position) {

  int setID = properties.at(position).getSetID();
  int maxHouses = 0;
  for (int i = 0; i < numProperties; i++) {
    if (properties.at(i).getSetID() == setID) {
      maxHouses = properties.at(i).getNumHouses();
      break;
    }
  }

  for (int i = 0; i < numProperties; i++) {
    if (properties.at(i).getSetID() == setID) {
      if (properties.at(i).getNumHouses() > maxHouses) {
        maxHouses = properties.at(i).getNumHouses();
      }
    }
  }

  return properties.at(position).getNumHouses() < maxHouses;
}

bool Monopoly::setOwned(std::vector<Player> &players, std::vector<Property> &properties, int &tempPosition,
                        Board &board, int &numProperties) {
  int playerOwner = 0;
  int setID = properties.at(tempPosition).getSetID();
  std::string player1 = properties.at(tempPosition).getPlayerOwner();
  int countInSetID = 0;

  for (int i = 1; i < numProperties; i++) {
    if (properties.at(i).getSetID() == setID) {
      countInSetID++;
    }
  }

  for (int i = 1; i < numProperties; i++) {
    if (properties.at(i).getSetID() == setID && properties.at(i).getPlayerOwner() == player1
        && properties.at(i).getPlayerOwner() != "None") {
      playerOwner++;
    }
  }
  return countInSetID == playerOwner;
}

void Monopoly::getMove(std::vector<Player> &players, Board &board, int &move) {
  std::cout << players.at(static_cast<long>(board.getPlayerTurn())).getName()
            << " please enter your move" << std::endl;
  std::cout << "1 to roll dice" << std::endl;
  std::cout << "2 to upgrade a property with a house or hotel" << std::endl;
  std::cout << "3 to sell a house or hotel" << std::endl;
  std::cout << "4 to leave the game" << std::endl;
  std::cout << "Your move: ";
  std::cin >> move;
}

void Monopoly::upgradeHouse(std::vector<Monopoly::Player> &players,
                            Monopoly::Board &board,
                            int &numPlayers,
                            int &numProperties,
                            Monopoly::Gamestate &gamestate,
                            std::vector<Monopoly::Property> &properties,
                            Monopoly::Rules &rules,
                            Monopoly::Space &space) {



  int countPutter = 0;
  int flag = 0;
  int maxSetID=0;
  for(int i=0;i<numProperties;i++){
    if(properties.at(i).getSetID() > maxSetID){
      maxSetID = properties.at(i).getSetID();
    }
  }

  int currentSetID=0;


  if (rules.getEvenHouses() == true) {
    while(currentSetID<=maxSetID) {
      for (int i = 1; i < numProperties; i++) {

        if (setOwned(players, properties, i, board, numProperties)
            && players.at(board.getPlayerTurn()).getName() == properties.at(i).getPlayerOwner()
            && (checkMaxHouses(properties, numProperties, i) || allEven(properties, numProperties, i))
            && (players.at(board.getPlayerTurn()).getCash() >= properties.at(i).getHouseCost() ||
                players.at(board.getPlayerTurn()).getCash() >= properties.at(i).getHotelCost())
            && properties.at(i).getNumHotels() != 1 && properties.at(i).getSetID() == currentSetID) {

          properties.at(i).setTempID(countPutter);
          countPutter++;
          flag = 1;
        }
      }
      currentSetID++;
    }
  }

  else if (rules.getEvenHouses() == false) {
    while(currentSetID<=maxSetID) {
      for (int i = 1; i < numProperties; i++) {
        if (setOwned(players, properties, i, board, numProperties)
            && players.at(board.getPlayerTurn()).getName() == properties.at(i).getPlayerOwner()
            && (players.at(board.getPlayerTurn()).getCash() >= properties.at(i).getHouseCost() ||
                players.at(board.getPlayerTurn()).getCash() >= properties.at(i).getHotelCost())
            && properties.at(i).getNumHotels() != 1 && properties.at(i).getSetID() == currentSetID) {

          properties.at(i).setTempID(countPutter);
          countPutter++;
          flag = 1;
        }
      }
      currentSetID++;
    }
  }


  if (flag == 0) {
    std::cout << "You don't have any properties that you can upgrade" << std::endl;
    return;
  }
  int maxTempID=0;
  for(int i=0;i<numProperties;i++){
    if(properties.at(i).getTempID() > maxTempID){
      maxTempID = properties.at(i).getTempID();
    }
  }
  int currTempID=0;



  std::cout << "Which property do you want to upgrade?" << std::endl;
  while(currTempID<=maxTempID){
    for (int i = 1; i < numProperties; i++) {
      if (properties.at(i).getTempID() != -1 && properties.at(i).getTempID() == currTempID) {
        if (properties.at(i).getNumHouses() < gamestate.getNumHousesBeforeHotels()) {
          std::cout << properties.at(i).getTempID() << " . " << properties.at(i).getName() << " [$"
                    << properties.at(i).getHouseCost() << "]" << std::endl;
        } else if (properties.at(i).getNumHouses() == gamestate.getNumHousesBeforeHotels()
            && properties.at(i).getNumHotels() != 1) {
          std::cout << properties.at(i).getTempID() << " . " << properties.at(i).getName() << " [$"
                    << properties.at(i).getHotelCost() << "]" << std::endl;
        }
      }
    }
    currTempID++;
  }


  int move;
  std::cout << "Your choice: ";
  std::cin >> move;

  for (int i = 0; i < numProperties; i++) {
    if (properties.at(i).getTempID() == move) {
      if (properties.at(i).getNumHouses() < gamestate.getNumHousesBeforeHotels()) {
        properties.at(i).setNumHouses(properties.at(i).getNumHouses() + 1);
        players.at(board.getPlayerTurn()).setCash(
            players.at(board.getPlayerTurn()).getCash() - properties.at(i).getHouseCost());

        break;
      } else {
        properties.at(i).setNumHotels(1);
        properties.at(i).setNumHouses(0);
        players.at(board.getPlayerTurn()).setCash(
            players.at(board.getPlayerTurn()).getCash() - properties.at(i).getHotelCost());
        break;
      }
    }
  }

  // To reset all temp IDs to -1 for future buying of houses
  for (int i = 0; i < numProperties; i++) {
    properties.at(i).setTempID(-1);
  }

}

void Monopoly::sellHouse(std::vector<Monopoly::Player> &players,
                         Monopoly::Board &board,
                         int &numPlayers,
                         int &numProperties,
                         Monopoly::Gamestate &gamestate,
                         std::vector<Monopoly::Property> &properties,
                         Monopoly::Rules &rules,
                         Monopoly::Space &space) {

  //IF EVEN HOUSES IS ENABLED, SELL PROPERTY WITH MOST NUMBER OF HOUSES
  //IF HOTEL PRESENT, SELL HOTEL FIRST

  int countPutter = 0;
  int flag = 0;
  int currSetID = 0;
  int maxSetID=0;
  for(int i=1;i<numProperties;i++){
    if(properties.at(i).getSetID()>maxSetID){
      maxSetID = properties.at(i).getSetID();
    }
  }



  if (rules.getEvenHouses() == false) {
    while(currSetID<=maxSetID) {
      for (int i = 1; i < numProperties; i++) {
        if (setOwned(players, properties, i, board, numProperties)
            && players.at(board.getPlayerTurn()).getName() == properties.at(i).getPlayerOwner()
            && (properties.at(i).getNumHouses() > 0 || properties.at(i).getNumHotels() == 1) && properties.at(i).getSetID() == currSetID) {

          properties.at(i).setTempID(countPutter);
          countPutter++;
          flag = 1;
        }
      }
      currSetID++;
    }
  }

  else if (rules.getEvenHouses() == true) {
    //int hotelFlag = 0;

    /*for (int i = 1; i < numProperties; i++) {
        if (properties.at(i).getNumHotels() == 1) {
            hotelFlag = 1;
        }
    }*/

    while(currSetID<=maxSetID){
      for(int i=1;i<numProperties;i++){

        int max = 0;
        int setID = properties.at(i).getSetID();

        for(int j=0;j<numProperties;j++){
          if(properties.at(j).getSetID() == setID){
            if(properties.at(j).getNumHouses()>max){
              max = properties.at(j).getNumHouses();
            }
          }
        }



        if(setOwned(players, properties, i, board, numProperties)
            && players.at(board.getPlayerTurn()).getName() == properties.at(i).getPlayerOwner()
            && properties.at(i).getSetID() == currSetID){

          if(setHasHotel(properties, numProperties, i) == true && properties.at(i).getNumHotels() != 1){
            continue;
          }
          else if(setHasHotel(properties, numProperties, i) == true && properties.at(i).getNumHotels() == 1){
            properties.at(i).setTempID(countPutter);
            countPutter++;
            flag = 1;
          }

          else if(setHasHotel(properties, numProperties, i) == false && properties.at(i).getNumHouses() == max && properties.at(i).getNumHouses() != 0 ){
            properties.at(i).setTempID(countPutter);
            countPutter++;
            flag = 1;
          }


        }
      }
      currSetID++;
    }



    /*if (hotelFlag == 1) {
        while(currSetID<=maxSetID) {
            for (int i = 1; i < numProperties; i++) {
                if (setOwned(players, properties, i, board, numProperties)
                    && players.at(board.getPlayerTurn()).getName() == properties.at(i).getPlayerOwner()
                    && properties.at(i).getNumHotels() == 1 && properties.at(i).getSetID() == currSetID) {
                    properties.at(i).setTempID(countPutter);
                    countPutter++;
                    flag = 1;
                }
            }
            currSetID++;
        }
    }


    if (hotelFlag == 0) {
        while (currSetID <= maxSetID) {
            for (int i = 1; i < numProperties; i++) {
                if (setOwned(players, properties, i, board, numProperties)
                    && players.at(board.getPlayerTurn()).getName() == properties.at(i).getPlayerOwner()
                    && properties.at(i).getNumHouses() == max && properties.at(i).getNumHotels() != 1
                    && properties.at(i).getSetID() == currSetID) {
                    properties.at(i).setTempID(countPutter);
                    countPutter++;
                    flag = 1;
                }
            }
            currSetID++;
        }

    }*/
  }

  if (flag == 0) {
    std::cout << "You don't have any upgrades that you can sell" << std::endl;
    return;
  }
  int maxTempID=0;
  for(int i=0;i<numProperties;i++){
    if(properties.at(i).getTempID() > maxTempID){
      maxTempID = properties.at(i).getTempID();
    }
  }
  int currTempID = 0;
  std::cout << "Which property do you want to downgrade?" << std::endl;
  while(currTempID<=maxTempID) {
    for (int i = 1; i < numProperties; i++) {
      if (properties.at(i).getTempID() != -1 && properties.at(i).getTempID() == currTempID) {
        if (properties.at(i).getNumHotels() != 1) {
          std::cout << properties.at(i).getTempID() << " . " << properties.at(i).getName() << " [$"
                    << properties.at(i).getHouseCost() / 2 << "]" << std::endl;
        } else {
          std::cout << properties.at(i).getTempID() << " . " << properties.at(i).getName() << " [$"
                    << properties.at(i).getHotelCost() / 2 << "]" << std::endl;
        }
      }
    }
    currTempID++;
  }

  int move;
  std::cout << "Your choice: ";
  std::cin >> move;

  for (int i = 1; i < numProperties; i++) {
    if (properties.at(i).getTempID() == move) {
      if (properties.at(i).getNumHotels() != 1) {
        properties.at(i).setNumHouses(properties.at(i).getNumHouses() - 1);
        players.at(board.getPlayerTurn()).setCash(
            players.at(board.getPlayerTurn()).getCash() + (properties.at(i).getHouseCost() / 2));
        break;
      } else {
        properties.at(i).setNumHotels(0);
        properties.at(i).setNumHouses(gamestate.getNumHousesBeforeHotels());
        players.at(board.getPlayerTurn()).setCash(
            players.at(board.getPlayerTurn()).getCash() + (properties.at(i).getHotelCost() / 2));
        break;
      }
    }
  }

  // To reset all temp IDs to -1 for future buying of houses
  for (int i = 1; i < numProperties; i++) {
    properties.at(i).setTempID(-1);
  }

}

void Monopoly::makeMove(std::vector<Player> &players, Board &board, int move, const std::string &fileName,
                        int &numProperties, Gamestate &gamestate, std::vector<Property> &properties, Rules &rules,
                        Space &space, int &numPlayers, DiceRoller &roller) {
  if (move == 1) {
    performMove(players, board, fileName, numProperties, gamestate, properties, rules, space,
                numPlayers, roller);
  } else if (move == 2) {
    upgradeHouse(players, board, numPlayers, numProperties, gamestate, properties, rules, space);
  } else if (move == 3) {
    sellHouse(players, board, numPlayers, numProperties, gamestate, properties, rules, space);
  } else if (move == 4) {
    leaveGame(players, board, properties, numProperties);
  }
}

void Monopoly::performMove(std::vector<Player> &players, Board &board, const std::string &fileName,
                           int &numProperties, Gamestate &gamestate, std::vector<Property> &properties, Rules &rules,
                           Space &space, int &numPlayers, DiceRoller &roller) {

  int count = 0;
  int tempPosition;
  char ans;
  int random1;
  int random2;
  int random;
  roller.setFlag(0);
  random1 = roller.getRandomFromFile();
  random2 = roller.getRandomFromFile();
  random1 = ((random1 % 6) + 1);
  random2 = ((random2 % 6) + 1);

  if (gamestate.getMaxDoubleReRolls() != 0 && (random1 == random2)) {
    roller.setFlag(1);
  } else if (gamestate.getMaxDoubleReRolls() != 0 && random1 != random2) {
    roller.setFlag(0);
  }
  random = random1 + random2;

  std::cout << players.at(board.getPlayerTurn()).getName() << ", you rolled a " << random << std::endl;
  players.at(board.getPlayerTurn()).setPosition(players.at(board.getPlayerTurn()).getPosition() + random);

  while (players.at(board.getPlayerTurn()).getPosition() > (numProperties - 1)) {
    players.at(board.getPlayerTurn()).setPosition(players.at(board.getPlayerTurn()).getPosition() - numProperties);
    ++count;
  }

  if (count == 1 && players.at(board.getPlayerTurn()).getPosition() != (0)) {
    players.at(board.getPlayerTurn()).setCash(
        players.at(board.getPlayerTurn()).getCash() + (count) * space.getGoCash());
  }else if(count > 1){
    players.at(board.getPlayerTurn()).setCash(
        players.at(board.getPlayerTurn()).getCash() + (count-1) * space.getGoCash());
  }

  tempPosition = static_cast<int>(players.at(board.getPlayerTurn()).getPosition());
  if (players.at(board.getPlayerTurn()).getPosition() == 0) {
    players.at(board.getPlayerTurn()).setCash(players.at(board.getPlayerTurn()).getCash() + space.getGoCash() *
        gamestate.getSalaryMultiplier());
    return;
  } else if (properties.at(tempPosition).getPlayerOwner() == "None"
      && players.at(board.getPlayerTurn()).getCash() >= properties.at(tempPosition).getPropertyCost()) {

    std::cout << "Would you like to buy " << properties.at(tempPosition).getName() << " for $"
              << properties.at(tempPosition).getPropertyCost() << "?" << std::endl;
    std::cout << "Rent on " << properties.at(tempPosition).getName() << " is $"
              << properties.at(tempPosition).getRent() << std::endl;
    std::cout << "Enter y for yes or n for no: ";
    std::cin >> ans;

    if (ans == 'y') {
      std::cout << players.at(board.getPlayerTurn()).getName() << " bought "
                << properties.at(tempPosition).getName() << " for $"
                << properties.at(tempPosition).getPropertyCost() << std::endl;

      properties.at(tempPosition).setPlayerOwner(players.at(board.getPlayerTurn()).getName());
      players.at(board.getPlayerTurn()).setCash(players.at(board.getPlayerTurn()).getCash() -
          properties.at(tempPosition).getPropertyCost());
    } else {
      if (rules.getAuctionProperty() == true) {
        Monopoly::startAuction(players, board, fileName, numProperties, gamestate, properties, rules, space,
                               numPlayers, roller, tempPosition);
      }
      return;
    }

  } else if (properties.at(tempPosition).getPlayerOwner() == "None"
      && players.at(board.getPlayerTurn()).getCash() < properties.at(tempPosition).getPropertyCost()) {

    std::cout << players.at(board.getPlayerTurn()).getName() << ", you don't have enough money to afford "
              << properties.at(tempPosition).getName() << ". " << properties.at(tempPosition).getName()
              << " costs $" << properties.at(tempPosition).getPropertyCost() << " but you only have $"
              << players.at(board.getPlayerTurn()).getCash() << std::endl;
    if (rules.getAuctionProperty() == true) {
      Monopoly::startAuction(players, board, fileName, numProperties, gamestate, properties, rules, space,
                             numPlayers, roller, tempPosition);
    }
    return;
  } else if (properties.at(tempPosition).getPlayerOwner() == players.at(board.getPlayerTurn()).getName()) {
    std::cout << players.at(board.getPlayerTurn()).getName() << ", you landed on "
              << properties.at(tempPosition).getName()
              << " which you already own" << std::endl;
    return;
  } else if (properties.at(tempPosition).getPlayerOwner() != "None"
      && (properties.at(tempPosition).getNumHouses() > 0 || properties.at(tempPosition).getNumHotels() == 1)) {
    int rent = 0;
    if (properties.at(tempPosition).getNumHouses() > 0) {
      rent = static_cast<int>(properties.at(tempPosition).getRentWithHouse() *
          pow(2, properties.at(tempPosition).getNumHouses() - 1));
    } else if (properties.at(tempPosition).getNumHotels() == 1) {
      rent = properties.at(tempPosition).getRentWithHotel();
    }
    //HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEe
    if (players.at(board.getPlayerTurn()).getCash() < rent) {
      if (sellForDebt(properties, numProperties, board, players, tempPosition, rent, gamestate) == true) {
        std::cout << players.at(board.getPlayerTurn()).getName() << " paid "
                  << properties.at(tempPosition).getPlayerOwner() << " $"
                  << rent << " for landing on "
                  << properties.at(tempPosition).getName() << std::endl;

        players.at(board.getPlayerTurn()).setCash(players.at(board.getPlayerTurn()).getCash() - rent);

        for (int i = 0; i < numPlayers; ++i) {

          if (properties.at(tempPosition).getPlayerOwner() == players.at(i).getName()) {
            players.at(i).setCash(players.at(i).getCash() + rent);
            break;
          }
        }
      } else {
        std::cout << players.at(board.getPlayerTurn()).getName() << " went bankrupt to "
                  << properties.at(tempPosition).getPlayerOwner() << " for landing on "
                  << properties.at(tempPosition).getName() << std::endl;

        int tempI;

        for (int i = 0; i < numPlayers; ++i) {
          if (properties.at(tempPosition).getPlayerOwner() == players.at(i).getName()) {
            tempI = i;
            players.at(i).setCash(players.at(i).getCash() + players.at(board.getPlayerTurn()).getCash());
            players.at(board.getPlayerTurn()).setCash(0);
            break;
          }
        }
        for (int j = 0; j < numProperties; ++j) {
          if (properties.at(j).getPlayerOwner() == players.at(board.getPlayerTurn()).getName()) {
            properties.at(j).setPlayerOwner(players.at(tempI).getName());
          }
        }
        leaveGame(players, board, properties, numProperties);
        return;
      }
    } else if (players.at(board.getPlayerTurn()).getCash() >= rent) {
      std::cout << players.at(board.getPlayerTurn()).getName() << " paid "
                << properties.at(tempPosition).getPlayerOwner() << " $"
                << rent << " for landing on "
                << properties.at(tempPosition).getName() << std::endl;
    }
  } else if (properties.at(tempPosition).getPlayerOwner() != "None") {
    if (setOwned(players, properties, tempPosition, board, numProperties) == true
        && players.at(board.getPlayerTurn()).getCash() >= properties.at(tempPosition).getRent()
            * gamestate.getPropSetMultiplier()) {

      std::cout << players.at(board.getPlayerTurn()).getName() << " paid "
                << properties.at(tempPosition).getPlayerOwner() << " $"
                << properties.at(tempPosition).getRent() * gamestate.getPropSetMultiplier() << " for landing on "
                << properties.at(tempPosition).getName() << std::endl;

      players.at(board.getPlayerTurn()).setCash(players.at(board.getPlayerTurn()).getCash() -
          properties.at(tempPosition).getRent()
              * gamestate.getPropSetMultiplier());

      for (int i = 0; i < numPlayers; ++i) {

        if (properties.at(tempPosition).getPlayerOwner() == players.at(i).getName()) {
          players.at(i).setCash(players.at(i).getCash() + properties.at(tempPosition).getRent()
              * gamestate.getPropSetMultiplier());
          break;
        }
      }
    } else if (setOwned(players, properties, tempPosition, board, numProperties) == true
        && players.at(board.getPlayerTurn()).getCash() < properties.at(tempPosition).getRent()
            * gamestate.getPropSetMultiplier()) {
      if (sellForDebt(properties, numProperties, board, players, tempPosition,
                      properties.at(tempPosition).getRent()
                          * gamestate.getPropSetMultiplier(), gamestate) == true) {

        std::cout << players.at(board.getPlayerTurn()).getName() << " paid "
                  << properties.at(tempPosition).getPlayerOwner() << " $"
                  << properties.at(tempPosition).getRent() * gamestate.getPropSetMultiplier()
                  << " for landing on "
                  << properties.at(tempPosition).getName() << std::endl;

        players.at(board.getPlayerTurn()).setCash(players.at(board.getPlayerTurn()).getCash() -
            properties.at(tempPosition).getRent()
                * gamestate.getPropSetMultiplier());

        for (int i = 0; i < numPlayers; ++i) {

          if (properties.at(tempPosition).getPlayerOwner() == players.at(i).getName()) {
            players.at(i).setCash(players.at(i).getCash() + properties.at(tempPosition).getRent()
                * gamestate.getPropSetMultiplier());
            break;
          }
        }
      } else {

        std::cout << players.at(board.getPlayerTurn()).getName() << " went bankrupt to "
                  << properties.at(tempPosition).getPlayerOwner() << " for landing on "
                  << properties.at(tempPosition).getName() << std::endl;
        int tempI;

        for (int i = 0; i < numPlayers; ++i) {
          if (properties.at(tempPosition).getPlayerOwner() == players.at(i).getName()) {
            tempI = i;
            players.at(i).setCash(players.at(i).getCash() + players.at(board.getPlayerTurn()).getCash());
            players.at(board.getPlayerTurn()).setCash(0);
            break;
          }
        }
        for (int j = 0; j < numProperties; ++j) {
          if (properties.at(j).getPlayerOwner() == players.at(board.getPlayerTurn()).getName()) {
            properties.at(j).setPlayerOwner(players.at(tempI).getName());
          }
        }
        leaveGame(players, board, properties, numProperties);
        return;
      }
    } else if (setOwned(players, properties, tempPosition, board, numProperties) == false
        && players.at(board.getPlayerTurn()).getCash() >= properties.at(tempPosition).getRent()) {

      std::cout << players.at(board.getPlayerTurn()).getName() << " paid "
                << properties.at(tempPosition).getPlayerOwner() << " $"
                << properties.at(tempPosition).getRent() << " for landing on "
                << properties.at(tempPosition).getName() << std::endl;

      players.at(board.getPlayerTurn()).setCash(players.at(board.getPlayerTurn()).getCash() -
          properties.at(tempPosition).getRent());

      for (int i = 0; i < numPlayers; ++i) {
        if (properties.at(tempPosition).getPlayerOwner() == players.at(i).getName()) {
          players.at(i).setCash(players.at(i).getCash() + properties.at(tempPosition).getRent());
          break;
        }
      }
      //HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
    } else if (setOwned(players, properties, tempPosition, board, numProperties) == false
        && players.at(board.getPlayerTurn()).getCash() < properties.at(tempPosition).getRent()) {
      if (sellForDebt(properties, numProperties, board, players, tempPosition,
                      properties.at(tempPosition).getRent(), gamestate) == true) {
        std::cout << players.at(board.getPlayerTurn()).getName() << " paid "
                  << properties.at(tempPosition).getPlayerOwner() << " $"
                  << properties.at(tempPosition).getRent() << " for landing on "
                  << properties.at(tempPosition).getName() << std::endl;

        players.at(board.getPlayerTurn()).setCash(players.at(board.getPlayerTurn()).getCash() -
            properties.at(tempPosition).getRent());

        for (int i = 0; i < numPlayers; ++i) {

          if (properties.at(tempPosition).getPlayerOwner() == players.at(i).getName()) {
            players.at(i).setCash(players.at(i).getCash() + properties.at(tempPosition).getRent());
            break;
          }
        }
      } else {

        std::cout << players.at(board.getPlayerTurn()).getName() << " went bankrupt to "
                  << properties.at(tempPosition).getPlayerOwner() << " for landing on "
                  << properties.at(tempPosition).getName() << std::endl;

        int tempI;
        for (int i = 0; i < numPlayers; ++i) {
          if (properties.at(tempPosition).getPlayerOwner() == players.at(i).getName()) {
            tempI = i;
            players.at(i).setCash(players.at(i).getCash() + players.at(board.getPlayerTurn()).getCash());
            players.at(board.getPlayerTurn()).setCash(0);
            break;
          }
        }
        for (int j = 0; j < numProperties; ++j) {
          if (properties.at(j).getPlayerOwner() == players.at(board.getPlayerTurn()).getName()) {
            properties.at(j).setPlayerOwner(players.at(tempI).getName());
          }
        }
        leaveGame(players, board, properties, numProperties);
        return;
      }
    }
    //HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEE
  } else if (properties.at(tempPosition).getPlayerOwner() != "None"
      && players.at(board.getPlayerTurn()).getCash() < properties.at(tempPosition).getRent()) {
    if (sellForDebt(properties, numProperties, board, players, tempPosition, properties.at(tempPosition).getRent(),
                    gamestate) == true) {
      std::cout << players.at(board.getPlayerTurn()).getName() << " paid "
                << properties.at(tempPosition).getPlayerOwner() << " $"
                << properties.at(tempPosition).getRent() << " for landing on "
                << properties.at(tempPosition).getName() << std::endl;

      players.at(board.getPlayerTurn()).setCash(players.at(board.getPlayerTurn()).getCash() -
          properties.at(tempPosition).getRent());

      for (int i = 0; i < numPlayers; ++i) {

        if (properties.at(tempPosition).getPlayerOwner() == players.at(i).getName()) {
          players.at(i).setCash(players.at(i).getCash() + properties.at(tempPosition).getRent());
          break;
        }
      }
    }

    std::cout << players.at(board.getPlayerTurn()).getName() << " went bankrupt to "
              << properties.at(tempPosition).getPlayerOwner() << " for landing on "
              << properties.at(tempPosition).getName() << std::endl;

    int tempI = 0;
    for (int i = 1; i < numPlayers + 1; ++i) {
      if (properties.at(tempPosition).getPlayerOwner() == players.at(i).getName()) {
        tempI = i;
        players.at(i).setCash(players.at(i).getCash() + players.at(board.getPlayerTurn()).getCash());
        players.at(board.getPlayerTurn()).setCash(0);
        break;
      }
    }
    for (int j = 0; j < numProperties; ++j) {
      if (properties.at(j).getPlayerOwner() == players.at(board.getPlayerTurn()).getName()) {
        properties.at(j).setPlayerOwner(players.at(tempI).getName());
      }
    }
    leaveGame(players, board, properties, numProperties);
    return;
  }
}

bool Monopoly::sellForDebt(std::vector<Monopoly::Property> &properties,
                           int numProperties,
                           Monopoly::Board &board,
                           std::vector<Monopoly::Player> &players,
                           int tempPosition, int moneyOwed, Monopoly::Gamestate &gamestate) {


  while (players.at(board.getPlayerTurn()).getCash() < moneyOwed) {


    int countPutter = 0;
    int flag = 0;
    for (int i = 1; i < numProperties; i++) {
      if (setOwned(players, properties, i, board, numProperties)
          && players.at(board.getPlayerTurn()).getName() == properties.at(i).getPlayerOwner()
          && (properties.at(i).getNumHouses() > 0 || properties.at(i).getNumHotels() == 1)) {
        properties.at(i).setTempID(countPutter);
        countPutter++;
        flag = 1;
      }
    }


    if (flag == 0) {
      return false;
    }

    std::cout << "You have $" << players.at(board.getPlayerTurn()).getCash() << " but you owe $" << moneyOwed
              << std::endl;
    std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;

    for (int i = 1; i < numProperties; i++) {
      if (properties.at(i).getTempID() != -1) {
        if (properties.at(i).getNumHotels() != 1) {

          std::cout << properties.at(i).getTempID() << " . " << properties.at(i).getName() << " [$"
                    << properties.at(i).getHouseCost() / 2 << "]" << std::endl;
        } else {
          std::cout << properties.at(i).getTempID() << " . " << properties.at(i).getName() << " [$"
                    << properties.at(i).getHotelCost() / 2 << "]" << std::endl;
        }
      }
    }

    int move;
    std::cout<<"Your choice:"<<std::endl;
    std::cin >> move;


    for (int i = 0; i < numProperties; i++) {
      if (properties.at(i).getTempID() == move) {
        if (properties.at(i).getNumHotels() != 1) {
          properties.at(i).setNumHouses(properties.at(i).getNumHouses() - 1);
          players.at(board.getPlayerTurn()).setCash(
              players.at(board.getPlayerTurn()).getCash() + (properties.at(i).getHouseCost() / 2));
          break;
        } else {
          properties.at(i).setNumHotels(0);
          properties.at(i).setNumHouses(gamestate.getNumHousesBeforeHotels());
          players.at(board.getPlayerTurn()).setCash(
              players.at(board.getPlayerTurn()).getCash() + (properties.at(i).getHotelCost() / 2));
          break;
        }
      }
    }

    for (int i = 1; i < numProperties; i++) {
      properties.at(i).setTempID(-1);
    }

  }
  return true;

}
bool Monopoly::setHasHotel(std::vector<Monopoly::Property> &properties, int numProperties, int position) {
  int flag=0;
  int setID = properties.at(position).getSetID();
  for(int i=1;i<numProperties;i++){
    if(properties.at(i).getSetID() == setID){
      if(properties.at(i).getNumHotels() == 1){
        flag=1;
      }
    }
  }

  if(flag == 1){
    return true;
  }
  return false;
}

void Monopoly::leaveGame(std::vector<Player> &players, Board &board, std::vector<Property> &properties, int numProperties) {
  players.at(static_cast<long>(board.getPlayerTurn())).setInGame(false);


  for(int i=1;i<numProperties;i++){
    if(properties.at(i).getPlayerOwner() == players.at(board.getPlayerTurn()).getName()){

      properties.at(i).setNumHouses(0);
      properties.at(i).setNumHotels(0);
    }

  }

  for (auto &iterator: properties) {
    if (iterator.getPlayerOwner() == players.at(board.getPlayerTurn()).getName()) {
      iterator.setPlayerOwner("None");
    }
  }




}

void Monopoly::startAuction(std::vector<Player> &players, Board &board, const std::string &fileName,
                            int &numProperties, Gamestate &gamestate, std::vector<Property> &properties, Rules &rules,
                            Space &space, int &numPlayers, DiceRoller &roller, int tempPosition) {
  int counter = 0;
  int tempPlayers;
  int currentBid;
  int highestBid = 0;
  std::string highestBidderName = " ";
  std::vector<Auction> auction(numPlayers);
  for (int j = 0; j < numPlayers; ++j) {
    auction.at(j).setName(players.at(j).getName());
  }

  std::cout << "Starting the auction for " << properties.at(tempPosition).getName() << std::endl;

  for (int i = 0; i < numPlayers; ++i) {
    if (highestBid == 0) {
      std::cout << "No one has bid on " << properties.at(tempPosition).getName() << " [$ "
                << properties.at(tempPosition).getPropertyCost() << "]" << " yet" << std::endl;
    } else {
      std::cout << "The current bid for " << properties.at(tempPosition).getName() << " [$ "
                << properties.at(tempPosition).getPropertyCost() << "]" << " is $" << highestBid
                << " by " << highestBidderName << std::endl;
    }
    std::cout << auction.at(i).getName() << ", enter a bid of at least $" << highestBid + 1
              << " to bid" << " on the property or a value less than that to leave the auction"
              << std::endl;
    std::cout << "Your bid: ";
    std::cin >> currentBid;
    if (currentBid >= highestBid + 1) {
      auction.at(i).setPlayerInAuction(true);
      highestBid = currentBid;
      highestBidderName = auction.at(i).getName();
    } else if (currentBid < highestBid + 1) {
      auction.at(i).setPlayerInAuction(false);
    }
  }

  for (int i = 0; i < numPlayers; ++i) {
    if (auction.at(i).getPlayerInAuction() == true)
      ++counter;
  }

  if (counter == 0) {
    std::cout << "No one decided to purchase " << properties.at(tempPosition).getName() << std::endl;
    return;
  }

  tempPlayers = counter;
  while (tempPlayers > 1) {
    for (int i = 0; i < numPlayers; ++i) {
      if (auction.at(i).getPlayerInAuction() == true && tempPlayers > 1) {
        if (highestBid == 0) {
          std::cout << "No one has bid on " << properties.at(tempPosition).getName() << " [$ "
                    << properties.at(tempPosition).getPropertyCost() << "]" << " yet" << std::endl;
        } else {
          std::cout << "The current bid for " << properties.at(tempPosition).getName() << " [$ "
                    << properties.at(tempPosition).getPropertyCost() << "]" << " is $" << highestBid
                    << " by " << highestBidderName << std::endl;
        }
        std::cout << auction.at(i).getName() << ", enter a bid of at least $" << highestBid + 1
                  << " to bid" << " on the property or a value less than that to leave the auction"
                  << std::endl;
        std::cout << "Your bid: ";
        std::cin >> currentBid;
        if (currentBid >= highestBid + 1) {
          highestBid = currentBid;
          highestBidderName = auction.at(i).getName();
        } else if (currentBid < highestBid + 1) {
          --tempPlayers;
          auction.at(i).setPlayerInAuction(false);
        }
      }
    }
  }

  std::cout << highestBidderName << " won " << properties.at(tempPosition).getName()
            << " for $" << highestBid << std::endl;

  properties.at(tempPosition).setPlayerOwner(highestBidderName);
  for (auto &iterator : players) {
    if (iterator.getName() == highestBidderName) {
      iterator.setCash(iterator.getCash() - highestBid);
    }
  }
}