#ifndef _BlockT_H_
#define _BlockT_H_

#include "pos.h"
#include "block.h"

class BlockT: public Block {
public:
    BlockT(int levelCre);
    BlockT(const BlockT& other): Block{other}{}
    const Pos* getConfig(int rotation);
    int getPossibleRotations();
    std::shared_ptr<Block>  getCopy() const;
    const static int possibleRotations;


private:
    static const Pos initialConfigs[4][blockSize];
};

#endif
