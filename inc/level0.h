#ifndef LEVEL0_H
#define LEVEL0_H

#include <string>
#include <vector>
#include <ctime>
#include "level.h"
#include "level1.h"

class Level0: public Level {
protected:
    std::vector<char> sequence;
public:
    Level0(int seed = time(NULL), std::string fileName = "sequence.txt");
    std::shared_ptr<Block> generateBlock() override;
    std::shared_ptr<Level> levelUp() override;
    std::shared_ptr<Level> levelDown() override;
};
#endif
