#include <iostream>
#include "blockL.h"

using namespace std;

const int BlockL::possibleRotations = 4;

const Pos BlockL::initialConfigs[possibleRotations][blockSize] =
        {{Pos{0, 2},  Pos{1, 0},  Pos{1, 1}, Pos{1, 2}},
         {Pos{1, 1},  Pos{-1, 0}, Pos{0, 0}, Pos{1, 0}},
         {Pos{1, 0},  Pos{0, 0},  Pos{0, 1}, Pos{0, 2}},
         {Pos{-1, 0}, Pos{-1, 1}, Pos{0, 1}, Pos{1, 1}}};

BlockL::BlockL(int levelCre) {
    levelCreated = levelCre;
    blockType = 'L';
    placed = false;
    scored = false;

    for (int i = 0; i < blockSize; ++i) {
        cells[i] = initialConfigs[0][i];
    }
    transformation.x = 0;
    transformation.y = 0;
    rotations = 0;
}

const Pos *BlockL::getConfig(int rotation) {
    return initialConfigs[rotation];
}

int BlockL::getPossibleRotations() {
    return possibleRotations;
}

std::shared_ptr<Block> BlockL::getCopy() const {
    return std::make_shared<BlockL>(*this);
}
