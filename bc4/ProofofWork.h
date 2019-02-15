//
// Created by zjp on 19-2-15.
//

#ifndef BLOCKCHAINCPP_POW_H
#define BLOCKCHAINCPP_POW_H

#include "Block.h"

class ProofofWork{
public:
    Block* block;
    //int difficultNum;

    ProofofWork(Block* b);
    std::string calculateHash(int64_t nonce);
    int64_t run(std::string& hash);
    bool validate();

private:
    std::string hashTransactions();
};

#endif //BLOCKCHAINCPP_POW_H
