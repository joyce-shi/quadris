#ifndef CELL_H
#define CELL_H

class Cell  {
    int r, c; //COnst causes problem in the creation loop in grid.cc ln 13

public:
  bool taken;
  char blocktype; // tells us what type of piece is occupying this cell (if occupied)

  /*____________________________________________________________________________
	PURPOSE: constructor
	Parameters: int r - Row number
              int c - Column Number
	Return:
	____________________________________________________________________________*/
	Cell();

	/*____________________________________________________________________________
	PURPOSE: set *this cell to the provided blocktype, also changes taken from default
	value false to true
	Parameters: char btype
	Return: Void
	____________________________________________________________________________*/
	void setCell(char btype);

};

#endif
