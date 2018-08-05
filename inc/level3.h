#ifndef LEVEL3_H
#define LEVEL3_H

#include <string>
#include <vector>
#include "level.h"
#include "level2.h"
#include "level4.h"

class Level3: public Level {
public:
    Level3(int seed = time(NULL), std::string fileName = "sequence.txt");
    std::shared_ptr<Block> generateBlock() override;
    std::shared_ptr<Level> levelUp() override;
    std::shared_ptr<Level> levelDown() override;
};
#endif
