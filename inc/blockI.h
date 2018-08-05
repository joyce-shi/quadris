#ifndef _BlockI_H_
#define _BlockI_H_

#include "pos.h"
#include "block.h"

class BlockI: public Block {
public:
    BlockI(int levelCre);
    BlockI(const BlockI& other): Block{other}{}
    const Pos* getConfig(int rotation);
    int getPossibleRotations();
    std::shared_ptr<Block>  getCopy() const;
    const static int possibleRotations;


private:
    static const Pos initialConfigs[2][blockSize];
};

#endif
