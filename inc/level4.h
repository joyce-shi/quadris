#ifndef LEVEL4_H
#define LEVEL4_H

#include <string>
#include <vector>
#include "level.h"
#include "level3.h"

class Level4: public Level {
public:
    Level4(int seed = time(NULL), std::string fileName = "sequence.txt");
    std::shared_ptr<Block> generateBlock() override;
    std::shared_ptr<Level> levelUp() override;
    std::shared_ptr<Level> levelDown() override;
};
#endif
