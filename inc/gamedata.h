#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "block.h"
#include <iostream>


struct GameData {
  int score;
  int hiScore;
  int level;
  std::shared_ptr<Block> nextBlock;

  void clearedRows (int numRows){
    if (numRows != 0){
      score += (level + numRows) * (level + numRows);
    }
    updateHighscore();
  }

  void clearedBlock (int blockLev){
    score += (blockLev + 1) * (blockLev + 1);
    updateHighscore();
  }

  void updateHighscore(){
    if (score > hiScore) { hiScore = score; }
  }
};

struct CellData{
  int x;
  int y;
  char blockType;
};

#endif
