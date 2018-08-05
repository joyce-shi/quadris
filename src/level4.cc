#include <iostream>
#include <fstream>

using namespace std;

#include <cstdlib>
#include "level4.h"
#include "level3.h"


// may be able to merge with level3

Level4::Level4(int seed, std::string fileName) { // may have to call the level constructor?
  this->fileName = fileName;
  this->seed = seed;

  level = 4;
}

// converts the random number generated to a specific block
// characters with two options => increased probability
// may be code duplication?
char blockconvert_4 (int random) {
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

std::shared_ptr<Block> Level4::generateBlock() {
  int random = rand() % 8;
  char retval = blockconvert_4(random);
  return whichBlock(retval);
}

std::shared_ptr<Level> Level4::levelUp() {
    return std::shared_ptr<Level4>(this);
}

std::shared_ptr<Level> Level4::levelDown() {
    return std::make_shared<Level3>(seed, fileName);
}
