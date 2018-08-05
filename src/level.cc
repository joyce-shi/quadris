#include "level.h"

// add a level as a parameter for the constructor

std::shared_ptr<Block> Level::whichBlock(char blockType) {
    if (blockType == 'I') {
        return std::make_shared<BlockI>(level);
    } else if (blockType == 'J') {
        return std::make_shared<BlockJ>(level);
    } else if (blockType == 'L') {
        return std::make_shared<BlockL>(level);
    } else if (blockType == 'O') {
        return std::make_shared<BlockO>(level);
    } else if (blockType == 'S') {
        return std::make_shared<BlockS>(level);
    } else if (blockType == 'T') {
        return std::make_shared<BlockT>(level);
    } else {
        return std::make_shared<BlockZ>(level);
    }
}
