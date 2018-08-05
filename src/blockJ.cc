#include <iostream>
#include "blockJ.h"

using namespace std;

const int BlockJ::possibleRotations = 4;

const Pos BlockJ::initialConfigs[possibleRotations][blockSize] =
        {{Pos{0,0}, Pos{1,0}, Pos{1,1}, Pos{1,2}},
         {Pos{-1,1}, Pos{-1,0}, Pos{0,0}, Pos{1,0}},
         {Pos{1,2}, Pos{0,2}, Pos{0,1}, Pos{0,0}},
         {Pos{1,0}, Pos{1,1}, Pos{0,1}, Pos{-1,1}}};

BlockJ::BlockJ(int levelCre)
{

  levelCreated = levelCre;
  blockType = 'J';
  placed = false;
    scored = false;

    for (int i = 0; i < blockSize; ++i) {
        cells[i] = initialConfigs[0][i];
    }
    transformation.x = 0;
    transformation.y = 0;
    rotations = 0;
}

const Pos* BlockJ::getConfig(int rotation) {
    return initialConfigs[rotation];
}

int BlockJ::getPossibleRotations() {
    return possibleRotations;
}

std::shared_ptr<Block>  BlockJ::getCopy() const {
    return std::make_shared<BlockJ>(*this);
}
