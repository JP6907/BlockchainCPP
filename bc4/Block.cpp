//
// Created by zjp on 19-2-15.
//
#include "Block.h"
#include "ProofofWork.h"
#include "../utils/sha256.h"
#include <sstream>

using namespace std;


Block::Block(std::vector<Transaction*> transactions, std::string prevBlockHash)
    : transactions(transactions), prevBlockHash(prevBlockHash){
    this->timeStamp = time(nullptr);
    this->hash = "";
    this->nonce = 0;
}

Block* Block::NewBlock(std::vector<Transaction*> transactions, std::string prevBlockHash) {
    Block* block = new Block(transactions,prevBlockHash);
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

Block* Block::NewGenesisBlock(Transaction* coinbase) {
    vector<Transaction*> vec;
    vec.push_back(coinbase);
    return NewBlock(vec,"");
}

Block* Block::DeserializeBlock(std::string d) {
    return nullptr;
}

std::string Block::hashTransactions() {
    stringstream ss;
    for (int i = 0; i < this->transactions.size(); ++i) {
        ss << this->transactions[i]->id;
    }
    string hash = sha256(ss.str());
    return hash;
}