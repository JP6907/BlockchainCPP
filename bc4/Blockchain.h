//
// Created by zjp on 19-2-15.
//

#ifndef BLOCKCHAINCPP_BLOCKCHAIN_H
#define BLOCKCHAINCPP_BLOCKCHAIN_H

#include <string>
#include <vector>
#include <map>
#include "Block.h"

class Blockchain{
public:
    std::string tip;  //保存最新区块的hash值
    std::map<std::string,Block*>* db;  //kv数据库

    static Blockchain* NewBlockchain(std::string address);
    void addBlock(std::vector<Transaction*> transactions);

    //找到包含未花费输出的交易
    std::vector<Transaction*> findUnspentTransactions(std::string address);
    //找到未交易的输出，可用于计算余额
    std::vector<TXOutput*> findUTXO(std::string address);
    //获取账户余额
    void getBalance(std::string address);


private:
    Blockchain(std::string tip,std::map<std::string,Block*>* db);
};
#endif //BLOCKCHAINCPP_BLOCKCHAIN_H
