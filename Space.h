
#ifndef MONOPOLY_SPACE_H
#define MONOPOLY_SPACE_H

#include <string>

namespace Monopoly {
    class Space {
    private:
        int goCash;
        std::string name;
    public:
        void setGoCash(int data);

        void setName(std::string data);

        int getGoCash();

        std::string getName();
    };

    void getStart(const std::string &fileName, Space &Go);
}
#endif //MONOPOLY_SPACE_H

