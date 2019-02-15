//
// Created by zjp on 19-2-15.
//
#include "Blockchain.h"

using namespace std;

map<string,Block*> g_db;

Blockchain::Blockchain(std::string tip, std::map<std::string, Block *> *db) {
    this->tip = tip;
    this->db = db;
}

Blockchain* Blockchain::NewBlockchain() {
    string tip;
    Block* genesis = Block::NewGenesisBlock();
    g_db[genesis->hash] = genesis;
    //g_db["last"] = genesis;
    tip = genesis->hash;

    Blockchain* bc = new Blockchain(tip,&g_db);
    return bc;
}

void Blockchain::addBlock(std::string data) {
    string lastHash = this->tip;
    //Block* p = g_db["last"];
    Block* p = g_db[lastHash];
    if(p== nullptr)
        return;

    //lastHash = p->hash;
    Block* newBlock = Block::NewBlock(data,lastHash);
    lastHash = newBlock->hash;
    //(*(this->db))["last"] = newBlock;
    (*(this->db))[lastHash] = newBlock;

    this->tip = lastHash;
}