#include <iostream>
#include <memory>
#include "blockO.h"

using namespace std;

const int BlockO::possibleRotations = 1;

const Pos BlockO::initialConfigs[1][blockSize] =
        {{Pos{0, 0}, Pos{0, 1}, Pos{1, 0}, Pos{1, 1}}};

BlockO::BlockO(int levelCre) {

    levelCreated = levelCre;
    blockType = 'O';
    placed = false;
    scored = false;

    for (int i = 0; i < blockSize; ++i) {
        cells[i] = initialConfigs[0][i];
    }
    transformation.x = 0;
    transformation.y = 0;
    rotations = 0;
}

const Pos *BlockO::getConfig(int rotation) {
    return initialConfigs[rotation];
}

int BlockO::getPossibleRotations() {
    return possibleRotations;
}

std::shared_ptr<Block> BlockO::getCopy() const {
    return std::make_shared<BlockO>(*this);
}
