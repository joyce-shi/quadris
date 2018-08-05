#include <iostream>
#include <fstream>

using namespace std;

#include <cstdlib>
#include "level3.h"

Level3::Level3(int seed, std::string fileName) { // may have to call the level constructor?
  this->fileName = fileName;
  this->seed = seed;

  level = 3;
}

// converts the random number generated to a specific block
// characters with two options => increased probability
// may be code duplication?
char blockconvert_3 (int random) {
  if (random == 0) {
    return 'I';
  } else if (random == 1) {
    return 'J';
  } else if (random == 7) {
    return 'L';
  } else if (random == 2) {
    return 'O';
  } else if ((random == 3) || (random == 5)) {
    return 'Z';
  } else if ((random == 4) || (random == 6)) {
    return 'S';
  } else {
    return 'T';
  }
}

std::shared_ptr<Block> Level3::generateBlock() {
  int random = rand() % 8;
  char retval = blockconvert_3(random);
  return whichBlock(retval);
}

std::shared_ptr<Level> Level3::levelUp() {
    return std::make_shared<Level4>(seed, fileName);
}

std::shared_ptr<Level> Level3::levelDown() {
    return std::make_shared<Level2>(seed, fileName);
}
