#ifndef _BlockJ_H_
#define _BlockJ_H_

#include "pos.h"
#include "block.h"

class BlockJ: public Block {
public:
    BlockJ(int levelCre);
    BlockJ(const BlockJ& other): Block{other}{}
    const Pos* getConfig(int rotation);
    int getPossibleRotations();
    std::shared_ptr<Block>  getCopy() const;
    const static int possibleRotations;


private:
    static const Pos initialConfigs[4][blockSize];
};

#endif
