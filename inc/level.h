#ifndef _Level_H_
#define _Level_H_

#include <string>
#include <ctime>

#include "block.h"
#include "blockI.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockO.h"
#include "blockS.h"
#include "blockT.h"
#include "blockZ.h"

class Level {
protected:
	int seed;
	std::string fileName;
    // calls the appropriate block constructor
public:
	std::shared_ptr<Block> whichBlock(char blockType);
int level;
	virtual std::shared_ptr<Block> generateBlock() = 0;
  virtual std::shared_ptr<Level> levelUp() = 0;
  virtual std::shared_ptr<Level> levelDown() = 0;

};

#endif
