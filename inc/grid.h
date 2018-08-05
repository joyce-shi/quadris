#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <memory>

#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "textdisplay.h"
#include "gamedata.h"
#include "cell.h"
#include "block.h"
#include "singleBlock.h"
#include "gdisplay.h"

class GraphicsDisplay;
class TextDisplay;
class Block;

//Grid Details
const int height = 15;
const int reserve = 3;
const int width = 11;

const int ROW_MAX = reserve + height;
const int COL_MAX = 11;

const int reserve_row = 3; //DO we need this>

//Block
const int no_blockpieces = 4;

//Nextblock Grid size
const int blockWidth = 4;
const int blockHieght = 2;

//levels
const int MIN_LEVEL = 0;
const int MAX_LEVEL = 4;

extern bool TEXTONLY;
extern int STARTLEVEL;
extern std::string SCRIPTFILE;
extern int SEED;



class Grid {

  std::shared_ptr<TextDisplay> td;//= nullptr; // the text display*/
  GraphicsDisplay *graphicsd;
  //std::shared_ptr<GraphicsDisplay> graphicsd;
  std::vector<std::vector<Cell> > theCells; // the actual grid
  std::vector<std::shared_ptr<Block>> boardBlocks; // the blocks that have been placed on the board

  std::shared_ptr<Level> curlevel; // the current level that the game is running on
  std::shared_ptr<Block> curBlock;
  std::shared_ptr<Block> hintBlock;
  bool hintActive = false;
  GameData gdata;
  int lvl4Moves = 0; // keeps track of moves played for level 4

  /*____________________________________________________________________________
  PURPOSE: return a level based on the inputed int
  Parameters: int level - level
  Return: void
  ____________________________________________________________________________*/
  void changeLevel(int level);

  /*____________________________________________________________________________
  PURPOSE: checks if position of b is valid (collisions, out of bound)
  takes in a block and modifies theCells in b to contain the blocks
  after placed  call isBottom
  Parameters: *Block
  Return:
  ____________________________________________________________________________*/
  void placeBlock(std::shared_ptr<Block> b, bool isHint = false);

  void addSingBlock();

  /*____________________________________________________________________________
  PURPOSE: checks if curBlock is at bottom, and push curBlock to vect and get
  nextblock
  Parameters:
  Return:
  ____________________________________________________________________________*/
  bool bottom(std::shared_ptr<Block> b);

  /*____________________________________________________________________________
  PURPOSE: checks if the cells in the Pos of b is already occupied or if any
  any cells are out of bounce
  Parameters: Block
  Return: true if all 4 cells are in valid positions
  ____________________________________________________________________________*/
  bool isValid(std::shared_ptr<Block> b);

  /*____________________________________________________________________________
  PURPOSE: removes a block from the grid
  Parameters: std::shared_ptr<Block>
  Return:
  ____________________________________________________________________________*/
  void removeBlock(std::shared_ptr<Block> b);

  /*____________________________________________________________________________
  PURPOSE: repeatly moves block b down till at bottom
  Parameters: std::shared_ptr<Block>
  Return:
  ____________________________________________________________________________*/
  void dropBlock(std::shared_ptr<Block> b, bool isHint = false);

  /*____________________________________________________________________________
  PURPOSE: checks if next block can be fit in the top left corner of the board,
  below the three reserve rows
  Parameters:
  Return: true if can place
  ____________________________________________________________________________*/
  bool GameOver();

  void restart();

  /*____________________________________________________________________________
  PURPOSE: Sends the Value(B, G, R, E) of a cell and the cells x, y
  to a textdisplay
  Parameters:
  Return:
  ____________________________________________________________________________*/
  GameData getGameData();

  /*____________________________________________________________________________
  PURPOSE: gets the CellData from the cell at x, y
  Parameters: x - x coordinate
  y - y coordinate
  Return: CellData - struct(x, y, blockType)
  ____________________________________________________________________________*/
  CellData getCellData(int x, int y);

  /*____________________________________________________________________________
  PURPOSE: checks if the row r, is filled with a block in ever column
  Parameters: r - row of the grid to be checked
  Return: bool - true if it i full, false otherwise
  ____________________________________________________________________________*/
  bool isRowFill(int r);

  /*____________________________________________________________________________
  PURPOSE: clears all cells in
  Parameters: r - row of the grid to be checked
  Return:
  ____________________________________________________________________________*/
  void clearRow(int r);

  /*____________________________________________________________________________
  PURPOSE: shifts all cells in column c, above the "start" down one cell
  Parameters: r - row of the grid to be checked
  start - the start cell, everything above it will get shifted down
  Return:
  this can be private
  ____________________________________________________________________________*/
  void shiftColDown(int start);

  /*******************************HINT*****************************************/
  /*____________________________________________________________________________
  PURPOSE: suggests the best possible move for the user to make, indicating it with '?'s
  Parameters:
  Return:
  ____________________________________________________________________________*/
  double bumpinessScore();

  double heightScore();

  double holesScore();

  double rowsScore(std::shared_ptr<Block> hint);

  double calculateHintScore(std::shared_ptr<Block> hint);

  /*************************HINT***********************************************/

  /*____________________________________________________________________________
  PURPOSE: shifts all cells in column c, above the "start" down one cell
  Parameters: r - row of the grid to be checked
  start - the start cell, everything above it will get shifted down
  Return:
  this can be private
  ____________________________________________________________________________*/
  void updateDisplays();

  void updateDisplays(int x, int y);

  bool isCleared(std::shared_ptr<Block> b);

public:
  /*____________________________________________________________________________
  PURPOSE: constructor
  Parameters: level_no - level game starts at (0, 1, 2, 3, 4, 5)
  Return:
  ____________________________________________________________________________*/
  Grid(int level_no = 0);

  /*____________________________________________________________________________
  PURPOSE: runs a command(cmd) on curBlock, if command is valid - no collidions
  no out of bound - than calls placeBlock
  Parameters: string cmd (LEFT, RIGHT, DOWN, DROP, RCW, RCCW)
  Return:
  ____________________________________________________________________________*/
  void changeBlock(std::string cmd);

  /*____________________________________________________________________________
  PURPOSE: levels Up
  Parameters:
  Return:
  ____________________________________________________________________________*/
  void levelUp();

  /*____________________________________________________________________________
  PURPOSE: Levels Down
  Parameters:
  Return:
  ____________________________________________________________________________*/
  void levelDown();

  void suggestHint();

  /*____________________________________________________________________________
  PURPOSE: immediately changes curBlock to be of type block
  Parameters: char block (I, J, L, S, Z, O, T)
  Return:
  ____________________________________________________________________________*/
  void replaceBlock(char block);

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
  // to allow for the grid to print

};

#endif
