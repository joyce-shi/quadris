#ifndef _BlockS_H_
#define _BlockS_H_

#include "pos.h"
#include "block.h"

class BlockS: public Block {
public:
    BlockS(int levelCre);
    BlockS(const BlockS& other): Block{other}{}
    const Pos* getConfig(int rotation);
    int getPossibleRotations();
    std::shared_ptr<Block>  getCopy() const;
    const static int possibleRotations;


private:
    static const Pos initialConfigs[2][blockSize];
};

#endif
