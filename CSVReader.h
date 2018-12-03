
#ifndef MONOPOLY_CSVREADER_H
#define MONOPOLY_CSVREADER_H

#include <string>
#include <fstream>

namespace Monopoly {

    class CSVReader {
    private:
        std::ifstream file;
        std::string fileName;

        std::string readUntilDelim(const std::string &delims);

    public:
        explicit CSVReader(const std::string &fileName);

        std::string readLine();

        void skipLine();

        std::string readNextFieldAsString();

        int readNextFieldAsInt();

        void skipField();
    };
}
#endif //MONOPOLY_CSVREADER_H
