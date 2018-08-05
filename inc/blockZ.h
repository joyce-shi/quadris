#ifndef _BlockZ_H_
#define _BlockZ_H_

#include "pos.h"
#include "block.h"

class BlockZ: public Block {
public:
    BlockZ(int levelCre);
    BlockZ(const BlockZ& other): Block{other}{}
    const Pos* getConfig(int rotation);
    int getPossibleRotations();
    std::shared_ptr<Block>  getCopy() const;
    const static int possibleRotations;

private:
    static const Pos initialConfigs[2][blockSize];
};

#endif
