#include <iostream>
#include "blockT.h"

using namespace std;

const int BlockT::possibleRotations = 4;

const Pos BlockT::initialConfigs[possibleRotations][blockSize] =
        {{Pos{0, 0},  Pos{0, 1}, Pos{0, 2},  Pos{1, 1}},
         {Pos{-1, 1}, Pos{0, 1}, Pos{1, 1},  Pos{0, 0}},
         {Pos{1, 2},  Pos{1, 1}, Pos{1, 0},  Pos{0, 1}},
         {Pos{1, 0},  Pos{0, 0}, Pos{-1, 0}, Pos{0, 1}}};

BlockT::BlockT(int levelCre) {

    levelCreated = levelCre;
    blockType = 'T';
    placed = false;
    scored = false;

    for (int i = 0; i < blockSize; ++i) {
        cells[i] = initialConfigs[0][i];
    }
    transformation.x = 0;
    transformation.y = 0;
    rotations = 0;
}

const Pos *BlockT::getConfig(int rotation) {
    return initialConfigs[rotation];
}

int BlockT::getPossibleRotations() {
    return possibleRotations;
}

std::shared_ptr<Block> BlockT::getCopy() const {
    return std::make_shared<BlockT>(*this);
}
