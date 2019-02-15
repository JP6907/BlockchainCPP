//
// Created by zjp on 19-2-15.
//
#include "Block.h"
#include "ProofofWork.h"

using namespace std;


Block::Block(std::string data, std::string prevBlockHash)
    : data(data), prevBlockHash(prevBlockHash){
    this->timeStamp = time(nullptr);
    this->hash = "";
    this->nonce = 0;
}

Block* Block::NewBlock(std::string data, std::string prevBlockHash) {
    Block* block = new Block(data,prevBlockHash);
    ProofofWork* pow = new ProofofWork(block);
    string hash = "";
    int64_t nonce = pow->run(hash);
    if(pow!= nullptr){  //释放
        delete pow;
        pow = nullptr;
    }
    block->hash = hash;
    block->nonce = nonce;
    return block;
}

std::string Block::Serialize(Block *b) {
    return "";
}

Block* Block::NewGenesisBlock() {
    return NewBlock("Genesis Block","");
}

Block* Block::DeserializeBlock(std::string d) {
    return nullptr;
}