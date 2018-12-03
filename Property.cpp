
#include "Property.h"
#include "CSVReader.h"
#include <fstream>
#include <string>
#include <vector>

Monopoly::Property::Property(const std::string &data, const std::string &ownerData) {
    fileName = data;
    file.open(data);
    playerOwner = ownerData;
}

void Monopoly::Property::setPropertyNumber(int data) {
    propertyNumber = data;
}

void Monopoly::Property::setType(const std::string &data) {
    type = data;
}

void Monopoly::Property::setSetID(int data) {
    setID = data;
}

void Monopoly::Property::setIntrasetID(int data) {
    intrasetID = data;
}

void Monopoly::Property::setName(const std::string &data) {
    name = data;
}

void Monopoly::Property::setPropertyCost(int data) {
    propertyCost = data;
}

void Monopoly::Property::setHouseCost(int data) {
    houseCost = data;
}

void Monopoly::Property::setHotelCost(int data) {
    hotelCost = data;
}


void Monopoly::Property::setRent(int data) {
    rent = data;
}

void Monopoly::Property::setRentWithHouse(int data) {
    rentWithHouse = data;
}

void Monopoly::Property::setRentWithHotel(int data) {
    rentWithHotel = data;
}

void Monopoly::Property::setPlayerOwner(const std::string &data) {
    playerOwner = data;
}

void Monopoly::Property::setTempID(int data) {
    tempID = data;
}

int Monopoly::Property::getNumProperties() {
    return numProperties;
}

int Monopoly::Property::getPropertyNumber() {
    return propertyNumber;
}

std::string Monopoly::Property::getType() {
    return type;
}

int Monopoly::Property::getSetID() {
    return setID;
}

int Monopoly::Property::getIntrasetID() {
    return intrasetID;
}

std::string Monopoly::Property::getName() {
    return name;
}

int Monopoly::Property::getPropertyCost() {
    return propertyCost;
}

int Monopoly::Property::getHouseCost() {
    return houseCost;
}

int Monopoly::Property::getHotelCost() {
    return hotelCost;
}

int Monopoly::Property::getRent() {
    return rent;
}

int Monopoly::Property::getRentWithHouse() {
    return rentWithHouse;
}

int Monopoly::Property::getRentWithHotel() {
    return rentWithHotel;
}

std::string Monopoly::Property::getPlayerOwner() {
    return playerOwner;
}

int Monopoly::Property::getTempID() {
    return tempID;
}

void Monopoly::Property::setNumHouses(int data) {
    numHouses = data;
}

void Monopoly::Property::setNumHotels(int data) {
    numHotels = data;
}

int Monopoly::Property::getNumHouses() {
    return numHouses;
}

int Monopoly::Property::getNumHotels() {
    return numHotels;
}

Monopoly::Property Monopoly::getProperty(const std::string &fileName, int i) {
    Monopoly::Property properties(fileName, "None");
    Monopoly::CSVReader reader(fileName);
    if (i == 0) {
        reader.skipLine();
        reader.skipLine();
        reader.skipLine();
        reader.skipLine();
        reader.skipField();
        reader.skipField();
        properties.setName(reader.readNextFieldAsString());
        properties.setPropertyNumber(i);
        return properties;
    }
    reader.skipLine();
    reader.skipLine();
    reader.skipLine();
    reader.skipLine();
    reader.skipLine();
    for (int j = 1; j < i; ++j) {
        reader.skipLine();
    }
    properties.setType(reader.readNextFieldAsString());
    properties.setSetID(reader.readNextFieldAsInt());
    properties.setIntrasetID(reader.readNextFieldAsInt());
    properties.setName(reader.readNextFieldAsString());
    properties.setPropertyCost(reader.readNextFieldAsInt());
    properties.setHouseCost(reader.readNextFieldAsInt());
    properties.setHotelCost(reader.readNextFieldAsInt());
    properties.setRent(reader.readNextFieldAsInt());
    properties.setRentWithHouse(reader.readNextFieldAsInt());
    properties.setRentWithHotel(reader.readNextFieldAsInt());
    properties.setPropertyNumber(i);
    return properties;
}

void Monopoly::getNumProperties(const std::string &fileName, int &numProperties) {
    Monopoly::CSVReader reader(fileName);
    reader.skipField();
    numProperties = reader.readNextFieldAsInt();
}

void Monopoly::setProperty(std::vector<Property> &properties, int numProperties, const std::string &fileName) {
    for (int i = 0; i < numProperties; ++i) {
        properties.at(i) = getProperty(fileName, i);
        properties.at(i).setTempID(-1);
        properties.at(i).setNumHouses(0);
        properties.at(i).setNumHotels(0);
    }
}