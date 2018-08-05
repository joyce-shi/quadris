#ifndef GRAPH_DIS
#define GRAPH_DIS

#include "window.h"
#include "grid.h"

class Cell;

const int NO_COL = 11;
const int NO_ROW = 18;

class GraphicsDisplay {
    const int cellsize = 30;

    const int width = cellsize * NO_COL;
    const int height = cellsize * NO_ROW + 40;

    const int cellsizeb = 18;

    std::vector<std::vector<char>> theNextBlock;

    Xwindow xw;

    GameData gd;

    public:
        /*____________________________________________________________________________
        PURPOSE: constructor
        Parameters:
        Return:
        ____________________________________________________________________________*/
       GraphicsDisplay();

       /*____________________________________________________________________________
       PURPOSE: Updates the gdata to contain the new level, scores, and nextblock
       Parameters:
       Return:
       ____________________________________________________________________________*/
       void updateGameData(GameData gData);

       /*____________________________________________________________________________
       PURPOSE: Updates display to contain the new data at a cell
       Parameters:
       Return:
       ____________________________________________________________________________*/
       void updateCellData(CellData cd);
       /*____________________________________________________________________________
       PURPOSE: Updates nextblock to contain the new data at a cell
       Parameters:
       Return:
       ____________________________________________________________________________*/
       void updateNextBlock(GameData gdata);

};

#endif
