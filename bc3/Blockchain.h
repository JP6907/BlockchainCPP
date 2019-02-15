//
// Created by zjp on 19-2-15.
//

#ifndef BLOCKCHAINCPP_BLOCKCHAIN_H
#define BLOCKCHAINCPP_BLOCKCHAIN_H

#include <string>
#include <map>
#include "Block.h"

class Blockchain{
public:
    std::string tip;  //保存最新区块的hash值
    std::map<std::string,Block*>* db;  //kv数据库

    static Blockchain* NewBlockchain();
    void addBlock(std::string data);

private:
    Blockchain(std::string tip,std::map<std::string,Block*>* db);
};
#endif //BLOCKCHAINCPP_BLOCKCHAIN_H
