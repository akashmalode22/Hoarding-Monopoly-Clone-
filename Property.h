
#ifndef MONOPOLY_PROPERTY_H
#define MONOPOLY_PROPERTY_H

#include <string>
#include <fstream>
#include <vector>

namespace Monopoly {
    class Property {
    private:

        int numProperties{};
        int propertyNumber{};
        std::string type;
        int setID{};
        int intrasetID{};
        std::string name;
        int propertyCost{};
        int houseCost{};
        int hotelCost{};
        int rent{};
        int rentWithHouse{};
        int rentWithHotel{};
        int tempID{};
        int numHouses{};
        int numHotels{};
        std::string playerOwner;
        std::string fileName;
        std::ifstream file;
    public:
        Property() = default;

        explicit Property(const std::string &data, const std::string &ownerData);

        void setPropertyNumber(int data);

        void setType(const std::string &data);

        void setSetID(int data);

        void setIntrasetID(int data);

        void setName(const std::string &data);

        void setPropertyCost(int data);

        void setHouseCost(int data);

        void setHotelCost(int data);

        void setRent(int data);

        void setRentWithHouse(int data);

        void setRentWithHotel(int data);

        void setPlayerOwner(const std::string &data);

        void setTempID(int data);

        void setNumHouses(int data);

        void setNumHotels(int data);

        int getNumHouses();

        int getNumHotels();

        int getTempID();

        int getNumProperties();

        int getPropertyNumber();

        std::string getType();

        int getSetID();

        int getIntrasetID();

        std::string getName();

        int getPropertyCost();

        int getHouseCost();

        int getHotelCost();

        int getRent();

        int getRentWithHouse();

        int getRentWithHotel();

        std::string getPlayerOwner();

    };

    void getNumProperties(const std::string &fileName, int &numProperties);

    Property getProperty(const std::string &fileName, int i);

    void setProperty(std::vector<Property> &properties, int numProperties, const std::string &fileName);
}

#endif //MONOPOLY_PROPERTY_H
