#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(int row, int col)
:rows{row}, cols{col} {
  //The display grid
  for (int x = 0; x < rows; ++x){
    vector<char> temp;
    for (int y = 0; y < cols; ++y){
      temp.push_back(' ');
    }
    theDisplay.push_back(temp);
    temp.clear();
  }

  //THe Nextblock Grid
  for (int x = 0; x < blockHieght; ++x){
    vector<char> temp;
    for (int y = 0; y < blockWidth; ++y){
      temp.push_back(' ');
    }
    theNextBlock.push_back(temp);
    temp.clear();
  }
}

void TextDisplay::updateGameData(GameData gData){
  gd = gData;

  //Clear the old block out
  for (int x = 0; x < blockHieght; ++x){
    for (int y = 0; y < blockWidth; ++y){
      theNextBlock[x][y] = ' ';
    }
  }

  //Update if there is a next block
  if (gData.nextBlock != nullptr){
    for (int i = 0; i < 4; ++i){
      int x = gData.nextBlock->cells[i].x;
      int y = gData.nextBlock->cells[i].y;
      theNextBlock[x][y] = gData.nextBlock->blockType;
    }
  }
}

void TextDisplay::updateCellData(CellData cd){
  if (cd.blockType == 'E'){
    theDisplay[cd.x][cd.y] = ' ';
  }
  else{
    theDisplay[cd.x][cd.y] = cd.blockType;
  }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td){


   int level = td.gd.level;
   int score = td.gd.score;
   int hiScore = td.gd.hiScore;
  //Display Score
  cout << "Level: " << level << endl;
  cout << "Score: " << score << endl;
  cout << "Hi Score: " << hiScore << endl;
  cout << "-----------" << endl;

  //Display board
  for (int x = 0; x < td.rows; ++x){
    for (int y = 0; y < td.cols; ++y){
      out << td.theDisplay[x][y];
    }
    out << endl;
  }
  cout << "-----------" << endl;

  //Display Next piece
  cout << "Next: " << endl;
  for (int x = 0; x < blockHieght; ++x){
    for (int y = 0; y < blockWidth; ++y){
      out << td.theNextBlock[x][y];
    }
    out << endl;
  }

  return out;
}
