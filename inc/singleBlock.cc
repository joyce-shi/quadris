#include <iostream>
#include "singleBlock.h"
#include "pos.h"

using namespace std;

// const Pos EMPTY = {-100, -100};

SingleBlock::SingleBlock() {
  levelCreated = 4;
  blockType = '*';
  placed = true;
  cells[0] = {0, MID};
  for (int i = 1; i < 4; ++i) {
    cells[i] = {0, MID};
  }
}

std::shared_ptr<Block> SingleBlock::getCopy() const {
    return std::make_shared<SingleBlock>(*this);
}

// functions to make it not abstract

const Pos* SingleBlock::getConfig(int rotation) {
  (void) rotation;
  //Pos retval = {0,0};
  return nullptr;//&retval;
}

int SingleBlock::getPossibleRotations() {
  return 0;
}

// functions to make it not abstract
