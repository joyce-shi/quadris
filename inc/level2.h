#ifndef LEVEL2_H
#define LEVEL2_H

#include <string>
#include <vector>
#include "level.h"
#include "level1.h"
#include "level3.h"

class Level2: public Level {
public:
    Level2(int seed = time(NULL), std::string fileName = "sequence.txt");
    std::shared_ptr<Block> generateBlock() override;
    std::shared_ptr<Level> levelUp() override;
    std::shared_ptr<Level> levelDown() override;
};
#endif
