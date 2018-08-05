#include "gdisplay.h"
#include <iostream>

using namespace std;

std::string t_hiscore = "tmp";
std::string t_score = "tmp";
std::string t_level = "tmp";

GraphicsDisplay::GraphicsDisplay() {
  xw.fillRectangle(0, 0, 500,
                  580, Xwindow::Black);
    // xw.fillRectangle(0, 0, width, height, Xwindow::Black);
    // main grid

    xw.fillRectangle(335, 275, 160, 300, Xwindow::Grey19);
    xw.fillRectangle(335, 5, 160, 265, Xwindow::Grey19); // do we want to merge
    // side panelling

    xw.drawBigString(95, 30, "Q  U  A  D  R  I  S", Xwindow::White);
    // title

    int hiScore = gd.hiScore;
    std::string s3;
    s3 = to_string(hiScore);
    xw.drawString(355, 30, "HIGH SCORE: " + s3, Xwindow::White);

    t_hiscore = "HISCORE: " + s3;
    //  xw.drawString(355, 30, "hi", Xwindow::White);
    // high score

    int score = gd.score;
    std::string s1;
    s1 = to_string(score);
    xw.drawString(355, 50, "SCORE: " + s1, Xwindow::White);

    t_score = "SCORE: " + s1;

    int level = gd.level;
    std::string s2;
    s2 = to_string(level);
    xw.drawString(355, 70, ("LEVEL: " + s2), Xwindow::White);

    t_level = "LEVEL: " + s2;
    //int level = graphics

    xw.drawString(355, 305, "NEXT BLOCK: ", Xwindow::White);
    // next block
    /*xw.fillRectangle(360, 330, 100, 100, Xwindow::White);

    int x = 330;
    int y = 360;
    int i = 0;
    while (i <= 100) {
      i = i + 20;
      xw.fillRectangle((y + i), x, cellsize,
                      1, Xwindow::Black); //top horizantal
    }*/

    for (int x = 0; x < blockHieght; ++x){
      vector<char> temp;
      for (int y = 0; y < blockWidth; ++y){
        temp.push_back(' ');
      }
      theNextBlock.push_back(temp);
      temp.clear();
    }

  }


  /*  xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), cellsize,
                    1, Xwindow::Black); //top horizantal
}*/
//*********************************
//const int startingx = 360;
//const int startingy = 330;

void GraphicsDisplay::updateGameData(GameData gdata) {

  int hiScore = gdata.hiScore;
  std::string s3;
  s3 = to_string(hiScore);
  xw.drawString(355, 30, t_hiscore, Xwindow::Grey19);
  xw.drawString(355, 30, "HIGH SCORE: " + s3, Xwindow::White);
  // high score

  t_hiscore = "HIGH SCORE: " + s3;

  int score = gdata.score;
  std::string s1;
  s1 = to_string(score);
  xw.drawString(355, 50, t_score, Xwindow::Grey19);
  xw.drawString(355, 50, "SCORE: " + s1, Xwindow::White);

  t_score = "SCORE: " + s1;

  int level = gdata.level;
  std::string s2;
  s2 = to_string(level);
  xw.drawString(355, 70, t_level, Xwindow::Grey19);
  xw.drawString(355, 70, ("LEVEL: " + s2), Xwindow::White);
  //int level = graphics

  t_level = "LEVEL: " + s2;
  /*
  *gd = gData;*
  //Update if there is a next block
  if (gData.nextBlock != nullptr){
    for (int i = 0; i < 4; ++i) {
      int x = gData.nextBlock->cells[i].x;
      int y = gData.nextBlock->cells[i].y;
      theNextBlock[x][y] = gData.nextBlock->blockType;
    }
  }*/

  updateNextBlock(gdata);
}

void GraphicsDisplay::updateNextBlock(GameData gdata) {

  //Clear the old block out
  for (int x = 0; x < blockHieght; ++x){
    for (int y = 0; y < blockWidth; ++y){
      theNextBlock[x][y] = ' ';
    }
  }

  //Update if there is a next block
  if (gdata.nextBlock != nullptr){
    for (int i = 0; i < 4; ++i){
      int x = gdata.nextBlock->cells[i].x;
      int y = gdata.nextBlock->cells[i].y;
      theNextBlock[x][y] = gdata.nextBlock->blockType;
    }
  }

 for (int x = 0; x < blockHieght; ++x) {
    for (int y = 0; y < blockWidth; ++y) {

      if (theNextBlock[x][y] == ' ') {
        xw.fillRectangle((y * cellsizeb + 350), (x * cellsizeb + 320), cellsizeb,
                        cellsizeb, Xwindow::Grey19);
         continue;

      } else if (theNextBlock[x][y] == 'L') {
        xw.fillRectangle((y * cellsizeb + 350), (x * cellsizeb + 320), cellsizeb,
                        cellsizeb, Xwindow::Orange);
      } else if (theNextBlock[x][y] == 'S') {
        xw.fillRectangle((y * cellsizeb + 350), (x * cellsizeb + 320), cellsizeb,
                        cellsizeb, Xwindow::Red);
      } else if (theNextBlock[x][y] == 'Z') {
        xw.fillRectangle((y * cellsizeb + 350), (x * cellsizeb + 320), cellsizeb,
                        cellsizeb, Xwindow::Green);
      } else if (theNextBlock[x][y] == 'T') {
        xw.fillRectangle((y * cellsizeb + 350), (x * cellsizeb + 320), cellsizeb,
                        cellsizeb, Xwindow::Magenta);
      } else if (theNextBlock[x][y] == 'O') {
        xw.fillRectangle((y * cellsizeb + 350), (x * cellsizeb + 320), cellsizeb,
                        cellsizeb, Xwindow::Yellow);
      } else if (theNextBlock[x][y] == 'I') {
        xw.fillRectangle((y * cellsizeb + 350), (x * cellsizeb + 320), cellsizeb,
                        cellsizeb, Xwindow::Cyan);
      } else if (theNextBlock[x][y] == ' ') {
        xw.fillRectangle((y * cellsizeb + 350), (x * cellsizeb + 320), cellsizeb,
                        cellsizeb, Xwindow::Brown);
      } else {
        xw.fillRectangle((y * cellsizeb + 350), (x * cellsizeb + 320), cellsizeb,
                        cellsizeb, Xwindow::Blue);
      }
      xw.fillRectangle((y * cellsizeb + 350), (x * cellsizeb + 320), cellsizeb,
                      1, Xwindow::Black); //top horizantal

      xw.fillRectangle((y * cellsizeb + 350), (x * cellsizeb + 320), 1,
                      cellsizeb, Xwindow::Black); //side bars

    }
  }
}
//************************************

void GraphicsDisplay::updateCellData(CellData cd) {
  if (cd.blockType == 'E') {
    xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), cellsize,
                    cellsize, Xwindow::Black);
    return;

  } else if (cd.blockType == 'L') {
    xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), cellsize,
                    cellsize, Xwindow::Orange);
  } else if (cd.blockType == 'S') {
    xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), cellsize,
                    cellsize, Xwindow::Red);
  } else if (cd.blockType == 'Z') {
    xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), cellsize,
                    cellsize, Xwindow::Green);
  } else if (cd.blockType == 'T') {
    xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), cellsize,
                    cellsize, Xwindow::Magenta);
  } else if (cd.blockType == 'O') {
    xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), cellsize,
                    cellsize, Xwindow::Yellow);
  } else if (cd.blockType == 'I') {
    xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), cellsize,
                    cellsize, Xwindow::Cyan);
  } else if (cd.blockType == '*') {
    xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), cellsize,
                    cellsize, Xwindow::Brown);
  } else {
    xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), cellsize,
                    cellsize, Xwindow::Blue);
  }
  xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), cellsize,
                  1, Xwindow::Black); //top horizantal

  xw.fillRectangle((cd.y * cellsize), (cd.x * cellsize + 40), 1,
                  cellsize, Xwindow::Black); //side bars
}
