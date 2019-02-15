//
// Created by zjp on 19-2-14.
//

#ifndef BLOCKCHAINCPP_BLOCKCHAIN_H
#define BLOCKCHAINCPP_BLOCKCHAIN_H

#define DIFFICULTY_NUM 4   //难度

#include "Block.h"
#include <vector>

class Blockchain{
public:
    Blockchain();
    void addBlock(Block bNew);

private:
    uint32_t _nDifficulty;  //难度值
    std::vector<Block> _vChain;   //记录区块链
    Block _getLastBlock() const;  //获取最后一个区块
};


#endif //BLOCKCHAINCPP_BLOCKCHAIN_H
