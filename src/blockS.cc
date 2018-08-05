#include <iostream>
#include "blockS.h"

using namespace std;

const int BlockS::possibleRotations = 2;

const Pos BlockS::initialConfigs[possibleRotations][blockSize] =
        {{Pos{0, 1}, Pos{0, 2}, Pos{1, 0}, Pos{1, 1}},
         {Pos{1, 1}, Pos{0, 1}, Pos{0, 0}, Pos{-1, 0}}};

BlockS::BlockS(int levelCre) {

    levelCreated = levelCre;
    blockType = 'S';
    placed = false;
    scored = false;

    for (int i = 0; i < blockSize; ++i) {
        cells[i] = initialConfigs[0][i];
    }
    transformation.x = 0;
    transformation.y = 0;
    rotations = 0;
}

const Pos *BlockS::getConfig(int rotation) {
    return initialConfigs[rotation];
}

int BlockS::getPossibleRotations() {
    return possibleRotations;
}

std::shared_ptr<Block> BlockS::getCopy() const {
    return std::make_shared<BlockS>(*this);
}
