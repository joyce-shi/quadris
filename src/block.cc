#include <iostream>
#include "block.h"

using namespace std;

Block::Block(const Block &other): blockType{other.blockType}, placed{other.placed},
                                  scored{other.scored}, levelCreated{other.levelCreated},
                                  rotations{other.rotations} {
    transformation.x = other.transformation.x;
    transformation.y = other.transformation.y;
    for (int i = 0; i < blockSize; ++i) {
        cells[i] = other.cells[i];
    }
}

Block::~Block() {}

void Block::down() {
    transformation.x++;
    for (int i = 0; i < blockSize; ++i){
        cells[i].x++;
    }
}

void Block::left() {
    transformation.y--;
    for (int i = 0; i < blockSize; ++i){
      cells[i].y--;
  }
}

void Block::right() {
    transformation.y++;
  for (int i = 0; i < blockSize; ++i){
      cells[i].y++;
  }
}
int abs(int n){
    if (n < 0) {n = 0-n;}
    return n;
}
void Block::rotate(bool clockwise) {
    int clockwiseOrCClockwise = clockwise ? 1 : -1;
    if (getPossibleRotations() == 0){
        rotations = 0;
    } else {
        rotations = (rotations + clockwiseOrCClockwise) % getPossibleRotations();
        if (rotations < 0) { rotations += getPossibleRotations(); }
    }

    for (int i = 0; i < blockSize; ++i) {
        cells[i].x = getConfig(rotations)[i].x + transformation.x;
        cells[i].y = getConfig(rotations)[i].y + transformation.y;
    }

}

void Block::setToHint() {
    blockType = '?';
}
