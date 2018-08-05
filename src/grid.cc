#include "grid.h"
#include "level.h"

//testing
#include <iostream>
#include <stdexcept>

using namespace std;

Grid::Grid(int level_no) { // SUBJECT TO CHANGE
    td = std::make_shared<TextDisplay>(ROW_MAX, COL_MAX);

    if(!TEXTONLY){
      //graphicsd = std::make_shared<GraphicsDisplay>();
      graphicsd = new GraphicsDisplay();
    }
    level_no = STARTLEVEL;

    theCells.clear();

    // this temporary std::vector<int> v; of cells allows you to create each row before pushing it onto theGrid
    for (int i = 0; i < (ROW_MAX); ++i) {
        vector<Cell> tmp;
        for (int j = 0; j < COL_MAX; ++j) {
            tmp.push_back(Cell()); // add each cell to the temporary row
        }
        theCells.push_back(tmp);
        tmp.clear(); // clear and repeat
    }

    changeLevel(level_no);

    //Get the blocks
    curBlock = curlevel->generateBlock();

    if (curBlock == nullptr) {
        throw out_of_range{"end of game - no more Blocks"};
    }

    for (int i = 0; i < reserve; ++i) {
        curBlock->down(); //moves it down 3 times so that its not in the reserved
    }
    placeBlock(curBlock);

    gdata = GameData{0, 0, level_no, nullptr};
    gdata.nextBlock = curlevel->generateBlock();

    updateDisplays();
}

void Grid::changeLevel(int level) { //Can this be optimisted? instead of if...
    // temporary to test level0
    if (level == 0) {
        curlevel = std::make_shared<Level0>(SEED, SCRIPTFILE);
    } else if (level == 1) {
        curlevel = std::make_shared<Level1>(SEED, SCRIPTFILE);
    } else if (level == 2) {
        curlevel = std::make_shared<Level2>(SEED, SCRIPTFILE);
        /*} else if (level == 3) {
          curlevel = newLevel1(); */
    } else {
        curlevel = std::make_shared<Level3>(SEED, SCRIPTFILE);
    }
}

void Grid::placeBlock(std::shared_ptr<Block> b, bool isHint) {
    if (curlevel->level != 4) {
        lvl4Moves = 0;
    }
    bool isBottom = bottom(b);

    //Update the cells
    for (int i = 0; i < no_blockpieces; ++i) {
        int x = b->cells[i].x;
        int y = b->cells[i].y;
        theCells[x][y].setCell(b->blockType);

        //Send update to the TextDisplay
         updateDisplays(x, y); //td->updateCellData(getCellData(x, y));
    } // modifies cells to hold block values
    if (!isHint) {
        //If that is the bottom then
        if (isBottom) {
            curBlock->placed = true;
            boardBlocks.push_back(curBlock);

            // 1. check if any rows are Filled
            for (int i = 0; i < no_blockpieces; ++i) {
                int row = curBlock->cells[i].x;
                int rowsFilled = 0;
                if (isRowFill(row)) {
                    //cout << "STATUS UPDATE: Row: " << row << "is Filled" << endl;
                    clearRow(row);
                    shiftColDown(row);
                    rowsFilled++;
                }
                //Update Score
                gdata.clearedRows(rowsFilled);
            }

            for (unsigned int i = 0; i < boardBlocks.size(); ++i) {
                if (isCleared(boardBlocks[i]) && (!boardBlocks[i]->scored)) {
                    gdata.clearedBlock(boardBlocks[i]->levelCreated);
                    boardBlocks[i]->scored = true;
                    //remove from vector
                }
            }

            //2. Add SingleBlock if neccessary
            if (gdata.level == 4) {
                lvl4Moves++;
                cout << lvl4Moves << endl;
                if (lvl4Moves == 5) {
                    addSingBlock();
                    lvl4Moves = 0;
                } // in the case that you have gone five moves without clearing a row
                // drop a midpiece onto the board, and then continue on
                // like normal
            }

            //3. Get a new curBlock
            if (gdata.nextBlock == nullptr) {
                throw out_of_range{"end of game - out of blocks"};
            }

            curBlock = gdata.nextBlock;
            for (int i = 0; i < reserve; ++i) {
                curBlock->down(); //moves it down 3 times so that its not in the reserved
            }
            if (!isValid(curBlock)) {
                throw out_of_range{"end of game - GameOver"};
            }
            placeBlock(curBlock);

            gdata.nextBlock = curlevel->generateBlock();//nextBlock = curlevel->generateBlock();
            updateDisplays();
        }
    }
}

void Grid::addSingBlock() {
    std::shared_ptr<Block> midpiece = std::make_shared<SingleBlock>();
    std::shared_ptr<Block> tmp = midpiece->getCopy();
    tmp->down();
    while (isValid(tmp)) {
        *midpiece = *tmp;
        tmp->down();
        // only add the block to the cells if it is a valid move
    }

    // modifies cells to hold block values
    int x = midpiece->cells[0].x;
    int y = midpiece->cells[0].y;
    theCells[x][y].setCell(midpiece->blockType);

    //Send update to the TextDisplay
    updateDisplays(x, y);

    //Clear any rows
    int row = midpiece->cells[0].x;
    int rowsFilled = 0;
    if (isRowFill(row)) {
        //cout << "STATUS UPDATE: Row: " << row << "is Filled" << endl;
        clearRow(row);
        shiftColDown(row);
        lvl4Moves = 0; // when row is cleared, resets counter
        rowsFilled++;
    }
    //Update Score
    gdata.clearedRows(rowsFilled);
    updateDisplays();
}

bool Grid::bottom(std::shared_ptr<Block> b) {
    //Check if u can move down
    std::shared_ptr<Block>tmp = b->getCopy();
    tmp->down();

    //If tmps isnt in a valid position then cur was a bottom
    return isValid(tmp) ? false : true;
}

void Grid::changeBlock(string cmd) {
    std::shared_ptr<Block>tmp = curBlock->getCopy();
    removeBlock(curBlock);

    //Makes blocks Heavy
    if ((gdata.level > 2) && (cmd != "DOWN") && (cmd != "DROP")) {
        curBlock->down();
    }

    //Run given command
    if (cmd == "LEFT") {
        curBlock->left();
    } else if (cmd == "RIGHT") {
        curBlock->right();
    } else if (cmd == "DOWN") {
        curBlock->down();
    } else if (cmd == "CLOCKWISE") {
        curBlock->rotate(true);
        cout << endl;
    } else if (cmd == "COUNTERCLOCKWISE") {
        curBlock->rotate(false);
    } else if (cmd == "DROP") {
        dropBlock(curBlock);
        return;
    } else if (cmd == "RESTART") {
        restart();
        return;
    } // performs the attempted operation

    bool validity = isValid(curBlock);

    if (!validity) {
        *curBlock = *tmp;
        cout << "Invalid Move";
    }  // only add the block to the cells if it is a valid move

    placeBlock(curBlock);
}

void Grid::replaceBlock(char block) {
    removeBlock(curBlock);
    curBlock = curlevel->whichBlock(block);
    for (int i = 0; i < reserve; ++i) {
        curBlock->down(); //moves it down 3 times so that its not in the reserved
    }
    placeBlock(curBlock);
}

bool Grid::isValid(std::shared_ptr<Block> b) {
    for (int i = 0; i < no_blockpieces; ++i) { // checking validity for each part of the block
        // checking if within grid bounds
        int x = b->cells[i].x;
        int y = b->cells[i].y;

        if ((x < 0) || (x >= ROW_MAX) || (y < 0) || (y >= COL_MAX)) {
            return false; // make sure x-coordinate is within bounds
        }

        // compare against cells
        if (theCells[x][y].taken) {
            return false;
        } // if the cell is already occupied, return false
    }
    return true;
}

void Grid::removeBlock(std::shared_ptr<Block> b) {
    for (int i = 0; i < no_blockpieces; ++i) {
        int x = b->cells[i].x;
        int y = b->cells[i].y;
        theCells[x][y].setCell('E');
        updateDisplays(x, y);//td->updateCellData(getCellData(x, y));
    }
}

bool Grid::GameOver() {
    return true;//!(isValid(&curBlock));
}

void Grid::restart() {
    td = std::make_shared<TextDisplay>(ROW_MAX, COL_MAX);
    graphicsd = new GraphicsDisplay();
    //graphicsd = std::make_unique<GraphicsDisplay>();
    theCells.clear();
    boardBlocks.clear();

    // this temporary std::vector<int> v; of cells allows you to create each row before pushing it onto theGrid
    for (int i = 0; i < (ROW_MAX); ++i) {
        vector<Cell> tmp;
        for (int j = 0; j < COL_MAX; ++j) {
            tmp.push_back(Cell()); // add each cell to the temporary row
        }
        theCells.push_back(tmp);
        tmp.clear(); // clear and repeat
    }

    changeLevel(gdata.level);

    //Get the blocks
    curBlock = curlevel->generateBlock();
    /*if (curBlock == nullptr) {
      throw out_of_range{"end of game"};
    }*/
    for (int i = 0; i < reserve; ++i) {
        curBlock->down(); //moves it down 3 times so that its not in the reserved
    }
    placeBlock(curBlock);

    gdata.score = 0;
    gdata.nextBlock = curlevel->generateBlock();

    updateDisplays();
}

void Grid::dropBlock(std::shared_ptr<Block> b, bool isHint) {
  (void) isHint;
    std::shared_ptr<Block>tmp = b->getCopy();
    removeBlock(b);
    while (true) {
        tmp->down();

        if (isValid(tmp)) {
            *b = *tmp;
        } else {
            break;
        } // only add the block to the cells if it is a valid move
    }
    placeBlock(b);
    //cout << "STATUS UPDATE: 4. Block Placed" << endl;
}

void Grid::levelUp() {
    if (gdata.level == MAX_LEVEL){ return; }
      curlevel = curlevel->levelUp();
      gdata.level = curlevel->level;
      updateDisplays();//td->updateGameData(getGameData());

}

void Grid::levelDown() {
    if (gdata.level == MIN_LEVEL){ return; }
      curlevel = curlevel->levelDown();
      gdata.level = curlevel->level;
      updateDisplays();//td->updateGameData(getGameData());
}

GameData Grid::getGameData() {
    //GameData gd = GameData {0,9000,0, nextBlock};
    return gdata;
}

CellData Grid::getCellData(int x, int y) {
    CellData cd;
    cd.x = x;
    cd.y = y;
    cd.blockType = theCells[x][y].blocktype;
    return cd;
}

bool Grid::isRowFill(int r) {
    //Iterate through every column in row r
    for (int i = 0; i < COL_MAX; ++i) {
        if (!theCells[r][i].taken) {
            return false;
        }
    }
    return true;
}

void Grid::clearRow(int r) {
    //Iterate through every column in row r
    for (int i = 0; i < COL_MAX; ++i) {
        theCells[r][i].setCell('E');

        //Send update to the TextDisplay
        updateDisplays(r, i);//td->updateCellData(getCellData(r, i));
    }
}

void Grid::shiftColDown(int start) {
    theCells.erase(theCells.begin() + start);
    vector<Cell> tmp;
    for (int j = 0; j < COL_MAX; ++j) {
        tmp.push_back(Cell()); // add each cell to the temporary row
    }
    theCells.insert(theCells.begin(), tmp);

    //Update all cells above row
    for (int i = 0; i <= start; ++i) {
        for (int j = 0; j < COL_MAX; ++j) {
            updateDisplays(i, j);//td->updateCellData(getCellData(i, j));
        }
    }
}

double Grid::bumpinessScore() {
    double avgHeight = 0;
    for (int i = 0; i < COL_MAX; ++i) {
        for (int j = ROW_MAX - 1; j >= 0; --j) {
            if (theCells[j][i].blocktype != 'E') {
                avgHeight += j / COL_MAX;
                break;
            }
        }
    }

    double varience = 0;
    for (int i = 0; i < COL_MAX; ++i) {
        for (int j = ROW_MAX - 1; j >= 0; --j) {
            if (theCells[j][i].blocktype != 'E') {
                varience += (avgHeight - j) * (avgHeight - j);
                break;
            }
        }
    }
    return varience;
}

double Grid::heightScore() {
    int heightSum = 0;
    for (int i = 0; i < COL_MAX; ++i) {
        for (int j = 0; j > ROW_MAX - 1; ++j) {
            if (theCells[j][i].blocktype != 'E') {
                heightSum += (15 - j);
                break;
            }
        }
    }
    return heightSum;
}

double Grid::holesScore() {

    int numOfHoles;
    // The first two for loops are for iterating through every cell in order to find a hole.
    for (int i = 0; i < COL_MAX; ++i) {
        for (int j = 0; j > ROW_MAX - 1; ++j) {
            //Holes can be of different sizes, but every hole must have a top-left corner. To avoid counting the same
            //   hole twice, these next two conditionals ensure have the top-left corner of something which could
            //   be a hole.
            if (theCells[j][i].blocktype == 'E') {
                if (((j != 0) && theCells[j - 1][i].blocktype != 'E') &&
                    (i == 0 || theCells[j][i - 1].blocktype != 'E')) {
                    //This is the process confirming we found a hole: iterate to the right of the selected 'top left
                    //  corner'. If there is every an opening both to the right and directly above our selected cell,
                    //  we have not found a hole.
                    for (int k = i; k < COL_MAX; ++k) {
                        if ((k + 1 == COL_MAX) || ((theCells[j][k + 1].blocktype != 'E')
                                                   && (theCells[j - 1][k + 1].blocktype != 'E'))) {
                            numOfHoles++;
                        } else if (((theCells[j][k + 1].blocktype != 'E') &&
                                    (theCells[j - 1][k + 1].blocktype != 'E'))) {
                            break;
                        }
                    }
                }
            }
        }
    }
    return numOfHoles;
}

double Grid::rowsScore(std::shared_ptr<Block> hint) {
    int completedRows = 0;
    for (int i = hint->cells[3].x; i <= hint->cells[0].x; ++i) {
        if (isRowFill(i)) { completedRows++; }
    }
    return completedRows;
}

double Grid::calculateHintScore(std::shared_ptr<Block> hint) {
    return rowsScore(hint) - holesScore() - heightScore() - bumpinessScore();
}

void Grid::suggestHint() {
    std::shared_ptr<Block>resetBlock = curlevel->whichBlock(curBlock->blockType);
    for (int n = 0; n < 3; ++n) {
        resetBlock->down();
    }

    hintBlock = resetBlock->getCopy();
    placeBlock(hintBlock);

    vector<vector<double>> hintScores;
    vector<double> rotationScores;

    for (int j = 0; j < curBlock->getPossibleRotations(); ++j) {
        rotationScores.clear();
        for (int i = 0; i < COL_MAX; ++i) {
            dropBlock(hintBlock, true);
            rotationScores.push_back(calculateHintScore(hintBlock));
            removeBlock(hintBlock);
            hintBlock->right();
            if (!isValid(hintBlock)) {
                break;
            }
            placeBlock(hintBlock, true);
        }
        hintBlock = resetBlock->getCopy();
        hintScores.push_back(rotationScores);
        hintBlock->rotate(true);
    }
    double maxScore = hintScores[0][0];
    int bestRotation;
    int bestCol;
    for (int k = 0; k < (signed) hintScores.size(); ++k) {
        for (int i = 0; i < (signed) hintScores[k].size(); ++i) {
            if (hintScores[k][i] >= maxScore) {
                maxScore = hintScores[k][i];
                bestRotation = k;
                bestCol = i;
            }
        }
    }

    removeBlock(hintBlock);

    //TODO: deal with memory management here
    hintBlock = resetBlock->getCopy();

    hintBlock->setToHint();
    for (int l = 0; l < bestRotation; ++l) {
        hintBlock->rotate(true);
    }
    for (int m = 0; m < bestCol; ++m) {
        hintBlock->right();
    }
    dropBlock(hintBlock, true);
    updateDisplays();
    hintActive = true;

}


void Grid::updateDisplays() {
    td->updateGameData(getGameData());
    if (TEXTONLY) { return; }
    GameData tmp = getGameData();
    graphicsd->updateGameData(tmp);
    //graphicsd->updateNextBlock(tmp);
}

void Grid::updateDisplays(int x, int y) {
    td->updateCellData(getCellData(x, y));
    if (TEXTONLY) { return; }
    graphicsd->updateCellData(getCellData(x, y));
}

bool Grid::isCleared(std::shared_ptr<Block> b) {
    for (int i = 0; i < blockSize; ++i) {
        int x = b->cells[i].x;
        int y = b->cells[i].y;
        if (theCells[x][y].taken) { return false; }
    }
    return true;

}


std::ostream &operator<<(std::ostream &out, const Grid &g) {
    out << *g.td;
    return out;
}


/*  for (int i = 0; i < no_blockpieces; ++i){
    int x = tmp->cells[i].x;
    int y = tmp->cells[i].y;
    cout << "(" << x << ", " << y << ") ";
  }
  cout << endl;
  */
