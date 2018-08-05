#include <iostream>
#include "blockI.h"

using namespace std;

const int BlockI::possibleRotations = 2;

const Pos BlockI::initialConfigs[possibleRotations][blockSize] =
        {{Pos{0, 0},  Pos{0, 1},  Pos{0, 2},  Pos{0, 3}},
         {Pos{-3, 0}, Pos{-2, 0}, Pos{-1, 0}, Pos{0, 0}}};

BlockI::BlockI(int levelCre) {
             levelCreated = levelCre;
             blockType = 'I';
             placed = false;
             scored = false;

             transformation.x = 0;
             transformation.y = 0;
             rotations = 0;

             for (int i = 0; i < blockSize; ++i) {
                 cells[i].x = initialConfigs[0][i].x + transformation.x;
                 cells[i].y = initialConfigs[0][i].y + transformation.y;
             }

}

const Pos *BlockI::getConfig(int rotation) {
    return initialConfigs[rotation];
}

int BlockI::getPossibleRotations() {
    return possibleRotations;
}

std::shared_ptr<Block> BlockI::getCopy() const {
    return std::make_shared<BlockI>(*this);
}
