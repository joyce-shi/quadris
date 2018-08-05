#ifndef LEVEL1_H
#define LEVEL1_H

#include <string>
#include <vector>
#include <ctime>
#include "level.h"
#include "level0.h"
#include "level2.h"

class Level1: public Level {
public:
    Level1(int seed = time(NULL), std::string fileName = "sequence.txt");
    std::shared_ptr<Block> generateBlock() override;
    std::shared_ptr<Level> levelUp() override;
    std::shared_ptr<Level> levelDown() override;
};
#endif
