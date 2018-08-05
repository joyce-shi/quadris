#include <iostream>
#include "blockZ.h"

using namespace std;

const int BlockZ::possibleRotations = 2;

const Pos BlockZ::initialConfigs[possibleRotations][blockSize] =
        {{Pos{0, 0},  Pos{0, 1}, Pos{1, 1}, Pos{1, 2}},
         {Pos{-1, 1}, Pos{0, 1}, Pos{0, 0}, Pos{1, 0}}};

BlockZ::BlockZ(int levelCre) {

    levelCreated = levelCre;
    blockType = 'Z';
    placed = false;
    scored = false;

    for (int i = 0; i < blockSize; ++i) {
        cells[i] = initialConfigs[0][i];
    }
    transformation.x = 0;
    transformation.y = 0;
    rotations = 0;
}

const Pos *BlockZ::getConfig(int rotation) {
    return initialConfigs[rotation];
}

int BlockZ::getPossibleRotations() {
    return possibleRotations;
}

std::shared_ptr<Block> BlockZ::getCopy() const {
    return std::make_shared<BlockZ>(*this);
}
