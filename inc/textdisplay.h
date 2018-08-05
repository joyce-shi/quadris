#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>

#include "grid.h"
#include "gamedata.h"

class TextDisplay {
  std::vector<std::vector<char> > theDisplay;
  std::vector<std::vector<char> > theNextBlock;
  int rows; //size of one dimension
  int cols;
  GameData gd;
 public:
   /*____________________________________________________________________________
   PURPOSE: constructor
   Parameters:
   Return:
   ____________________________________________________________________________*/
  TextDisplay(int row, int col);

  /*____________________________________________________________________________
  PURPOSE: Updates the gData to contain the new level, scores, and nextblock
  Parameters:
  Return:
  ____________________________________________________________________________*/
  void updateGameData(GameData gData);

  /*____________________________________________________________________________
  PURPOSE: Updates theDisplay to contain the new data at a cell
  Parameters:
  Return:
  ____________________________________________________________________________*/
  void updateCellData(CellData cd);

  /*____________________________________________________________________________
  PURPOSE: Output Opperator
  Parameters:
  Return:
  ____________________________________________________________________________*/
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
