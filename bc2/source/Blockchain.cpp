//
// Created by zjp on 19-2-14.
//
#include "Blockchain.h"

Blockchain::Blockchain(Block* p) {
    blocks.clear();
    blocks.push_back(p);
}

Blockchain::~Blockchain(){
    for (int i = 0; i < blocks.size(); ++i) {
        if(blocks[i]!= nullptr){
            delete blocks[i];
            blocks[i] = nullptr;
        }
    }
}

void Blockchain::AddBlock(std::string dataIn) {
    Block* prev = blocks.back();
    Block* newBlock = new Block(dataIn,prev->_hash);
    newBlock->ProofOfWork(DIFFICULTY_NUM);
    blocks.push_back(newBlock);
}
