//
// Created by zjp on 19-2-14.
//

#ifndef BLOCKCHAINCPP_BLOCKCHAIN_H
#define BLOCKCHAINCPP_BLOCKCHAIN_H

#define DIFFICULTY_NUM 4

#include "Block.h"
#include <vector>

class Blockchain{
public:
    Blockchain(Block *b);
    std::vector<Block*> blocks;
    void AddBlock(std::string dataIn);
    ~Blockchain();

private:

};

#endif //BLOCKCHAINCPP_BLOCKCHAIN_H
