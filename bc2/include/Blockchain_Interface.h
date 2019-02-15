//
// Created by zjp on 19-2-15.
//

#ifndef BLOCKCHAINCPP_BLOCKCHAIN_INTERFACE_H
#define BLOCKCHAINCPP_BLOCKCHAIN_INTERFACE_H

#include "Blockchain.h"
#include "Block.h"
#include "string"

class BC_Interface{
public:
    static Block* NewGenesisBlock() {
        return NewBlock("Genesis Block", "");
    }

    static Blockchain* NewBlockchain() {
        Block* pblock = NewGenesisBlock();
        Blockchain* p = new Blockchain(pblock);
        return  p;
    }
    static Block* NewBlock(std::string datain, std::string prevBlockHash) {
        Block* p = new Block( datain, prevBlockHash);
        p->ProofOfWork(DIFFICULTY_NUM);
        return p;
    }
};

#endif //BLOCKCHAINCPP_BLOCKCHAIN_INTERFACE_H
