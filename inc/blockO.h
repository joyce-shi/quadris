#ifndef _BlockO_H_
#define _BlockO_H_

#include "pos.h"
#include "block.h"

class BlockO: public Block {
public:
    BlockO(int levelCre);
    BlockO(const BlockO& other): Block{other}{}
    const Pos* getConfig(int rotation);
    int getPossibleRotations();
    std::shared_ptr<Block>  getCopy() const;
    const static int possibleRotations;


private:
    static const Pos initialConfigs[1][blockSize];
};

#endif
