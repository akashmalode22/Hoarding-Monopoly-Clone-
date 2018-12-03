
#include "CSVReader.h"
#include <limits>
#include <ios>
#include <sstream>
#include <iostream>

Monopoly::CSVReader::CSVReader(const std::string &fileName) : fileName(fileName) {
    file.open(fileName);
    if (!file.good()) {
        std::cout << "Failed to open " << fileName << std::endl;
    }
}

std::string Monopoly::CSVReader::readLine() {
    return readUntilDelim("\n");
}

std::string Monopoly::CSVReader::readUntilDelim(const std::string &delims) {
    char c;
    std::string stuff;
    if (file.good()) {
        while (file.get(c)) {                              //c is not one of the delimiters
            if (delims.find_first_of(c) == std::string::npos) {
                stuff.push_back(c);
            } else {
                break;
            }
        }
    } else {
        std::cout << "Error when reading from " << fileName << std::endl;
    }
    return stuff;
}

void Monopoly::CSVReader::skipLine() {
    readLine();
}

std::string Monopoly::CSVReader::readNextFieldAsString() {
    return readUntilDelim(",\n");
}

int Monopoly::CSVReader::readNextFieldAsInt() {
    std::string field = readNextFieldAsString();
    std::stringstream ss(field);
    int num;
    if (!(ss >> num)) {
        std::cout << field << " wasn't a number" << std::endl;
    }
    return num;
}

void Monopoly::CSVReader::skipField() {
    readNextFieldAsString();
}
