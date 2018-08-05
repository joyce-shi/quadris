#include <iostream>
#include <fstream>

using namespace std;

#include <cstdlib>
#include "level1.h"

Level1::Level1(int seed, std::string fileName) { // may have to call the level constructor?
  this->fileName = fileName;
  this->seed = seed;

  level = 1;
}

// converts the random number generated to a specific block
// characters with two options => increased probability
// may be code duplication?
char blockconvert (int random) {
  if ((random == 0) || (random == 1)) {
    return 'I';
  } else if ((random == 2) || (random == 3)) {
    return 'J';
  } else if ((random == 4) || (random == 5)) {
    return 'L';
  } else if ((random == 6) || (random == 7)) {
    return 'O';
  } else if ((random == 8) || (random == 9)) {
    return 'T';
  } else if (random == 10) {
    return 'S';
  } else {
    return 'Z';
  }
}

std::shared_ptr<Block> Level1::generateBlock() {
  int random = rand() % 11;
  char retval = blockconvert(random);
  return whichBlock(retval);
}

std::shared_ptr<Level> Level1::levelUp() {
    return std::make_shared<Level2>(seed,fileName);
}

std::shared_ptr<Level> Level1::levelDown() {
    return std::make_shared<Level0>(seed, fileName);
}
