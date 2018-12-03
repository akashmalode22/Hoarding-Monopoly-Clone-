
#include "Space.h"
#include "CSVReader.h"

void Monopoly::Space::setGoCash(int data) {
    goCash = data;
}

void Monopoly::Space::setName(std::string data) {
    name = std::move(data);
}

int Monopoly::Space::getGoCash() {
    return goCash;
}

std::string Monopoly::Space::getName() {
    return name;
}

void Monopoly::getStart(const std::string &fileName, Space &Go) {
    CSVReader reader(fileName);
    reader.skipLine();
    reader.skipLine();
    reader.skipLine();
    reader.skipLine();
    reader.skipField();
    Go.setGoCash(reader.readNextFieldAsInt());
    Go.setName(reader.readNextFieldAsString());
}
