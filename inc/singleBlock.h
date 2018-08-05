#ifndef _SINGLEBLOCK_H_
#define _SINGLEBLOCK_H_

#include "pos.h"
#include "block.h"

// the SingleBlock class exists for the mid piece that gets added to the
// fourth level if rows are not cleared every 5 moves
const int MID = 5;
// onst Pos EMPTY = {}

class SingleBlock: public Block {
public:
    SingleBlock();
    std::shared_ptr<Block> getCopy() const;

    const Pos* getConfig(int rotation) override;
    // to make it not pure virtual
    int getPossibleRotations() override;

};

#endif
