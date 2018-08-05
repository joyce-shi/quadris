#include <iostream>
#include <fstream>

using namespace std;

#include <cstdlib>
#include "level2.h"

Level2::Level2(int seed, std::string fileName) { // may have to call the level constructor?
  this->fileName = fileName;
  this->seed = seed;

  level = 2;
}

// converts the random number generated to a specific block
// characters with two options => increased probability
// may be code duplication?
char blockconvert_2 (int random) {
  if (random == 0) {
    return 'I';
  } else if (random == 1) {
    return 'J';
  } else if (random == 2) {
    return 'O';
  } else if (random == 3) {
    return 'T';
  } else if (random == 4) {
    return 'S';
  } else if (random == 5) {
    return 'L';
  } else {
    return 'Z';
  }
}

std::shared_ptr<Block> Level2::generateBlock() {
  int random = rand() % 6;
  char retval = blockconvert_2(random);
  return whichBlock(retval);
}

std::shared_ptr<Level> Level2::levelUp() {
    return std::make_shared<Level3>(seed, fileName);
}

std::shared_ptr<Level> Level2::levelDown() {
    return std::make_shared<Level1>(seed, fileName);
}
