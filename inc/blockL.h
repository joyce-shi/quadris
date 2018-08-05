#ifndef _BlockL_H_
#define _BlockL_H_

#include "pos.h"
#include "block.h"

class BlockL: public Block {
public:
    BlockL(int levelCre);
    BlockL(const BlockL& other): Block{other}{}
    const Pos* getConfig(int rotation);
    int getPossibleRotations();
    std::shared_ptr<Block>  getCopy() const;
    const static int possibleRotations;


private:
    static const Pos initialConfigs[4][blockSize];
};

#endif
