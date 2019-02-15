//
// Created by zjp on 19-2-15.
//

#ifndef BLOCKCHAINCPP_BLOCKCHAINITR_H
#define BLOCKCHAINCPP_BLOCKCHAINITR_H

#include "string"
#include "Blockchain.h"
#include <map>

/**
 * 迭代器
 */
class BlockchainItr{
public:
    std::string currentHash;
    std::map<std::string,Block*>* db;

    BlockchainItr(Blockchain* bc);
    Block* nextBlock();
};

#endif //BLOCKCHAINCPP_BLOCKCHAINITR_H
