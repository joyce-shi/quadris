#include <iostream>
#include <fstream>

using namespace std;

#include "level0.h"

Level0::Level0(int seed, std::string fileName) {
    this->fileName = fileName;
    this->seed = seed;

    this->level = 0;

    ifstream file{fileName};
    string s;
    while (file >> s) {
      sequence.push_back(s[0]);
    }
    // read all of the elements from the file into an array
}

std::shared_ptr<Block> Level0::generateBlock() {
    if (sequence.size() == 0) {
      return nullptr;
    }
    char tmp = sequence.front();
    sequence.erase(sequence.begin());
    return whichBlock(tmp);

    // generate blocks based on the elements in the file, popping off
    // the vector stack as you go
}

std::shared_ptr<Level> Level0::levelUp() {
  return std::make_shared<Level1>(seed, fileName);
  //  return Level1(seed);
}

std::shared_ptr<Level> Level0::levelDown() {
    return std::shared_ptr<Level0>(this);
}
