#ifndef _Block_H_
#define _Block_H_

#include <memory>
#include "pos.h"

const int blockSize = 4;

class Block {
public:
    char blockType;
    bool placed; //Is it fixed in its position
    bool scored; //Has the score been counted?
    int levelCreated;
    int rotations;
    Pos transformation;


    Block() {}

    Block(const Block &other);

    ~Block();

    virtual const Pos *getConfig(int rotation) = 0;

    virtual int getPossibleRotations()=0;

    Pos cells[blockSize];

    void left();

    void right();

    void down();

    void rotate(bool clockwise);

    virtual std::shared_ptr<Block>getCopy() const =0;

    bool isCleared();

    void setToHint();

};

#endif
