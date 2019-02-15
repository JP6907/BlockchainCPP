//
// Created by zjp on 19-2-15.
//
#include "BlockchainItr.h"

BlockchainItr::BlockchainItr(Blockchain *bc) {
    this->currentHash = bc->tip;
    this->db = bc->db;
}

Block* BlockchainItr::nextBlock() {
    Block* block = (*(this->db))[this->currentHash];
    this->currentHash = block->prevBlockHash;
    return block;
}
