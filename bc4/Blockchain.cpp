//
// Created by zjp on 19-2-15.
//
#include "Blockchain.h"
#include "BlockchainItr.h"
#include <iostream>

using namespace std;

map<string,Block*> g_db;

Blockchain::Blockchain(std::string tip, std::map<std::string, Block *> *db) {
    this->tip = tip;
    this->db = db;
}

Blockchain* Blockchain::NewBlockchain(std::string address) {
    string tip;
    const string genesisCoinbaseData = "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks";
    Transaction* cbtx = NewCoinbaseTX(address,genesisCoinbaseData);
    Block* genesis = Block::NewGenesisBlock(cbtx);

    g_db[genesis->hash] = genesis;
    //g_db["last"] = genesis;
    tip = genesis->hash;

    Blockchain* bc = new Blockchain(tip,&g_db);
    return bc;
}

void Blockchain::addBlock(std::vector<Transaction*> transactions) {
    string lastHash = this->tip;
    //Block* p = g_db["last"];
    Block* p = g_db[lastHash];
    if(p== nullptr)
        return;

    //lastHash = p->hash;
    Block* newBlock = Block::NewBlock(transactions,lastHash);
    lastHash = newBlock->hash;
    //(*(this->db))["last"] = newBlock;
    (*(this->db))[lastHash] = newBlock;

    this->tip = lastHash;
}

std::vector<Transaction*> Blockchain::findUnspentTransactions(std::string address) {
    BlockchainItr* bci = new BlockchainItr(this);
    vector<Transaction*> unspentTXS;  //包含未消费输出的交易
    map<string,vector<int>> spentTXOs;  //已经消费的交易的输出编号  交易id-输出编号

    while(1){
        Block* block = bci->nextBlock();
        //每个区块的每笔交易
        for (int txIndex = 0; txIndex < block->transactions.size(); ++txIndex) {
            string txID = block->transactions[txIndex]->id;

            //交易的每笔输出
            for (int outIndex = 0; outIndex < block->transactions[txIndex]->vout.size(); ++outIndex) {

                //一笔交易输出只能被后面的交易输入所引用
                //遍历区块的时候是从后往前搜索
                //因此当搜索到某个区块的某笔交易时，就已经知道这笔交易的输出是否已经被花费了
                //首先检查输出是否已经包含在输入中，即检查是否已经被花费
                if(spentTXOs[txID].size()!=0){
                    for (int i = 0; i < spentTXOs[txID].size(); ++i) {
                        if(spentTXOs[txID][i] == outIndex) //已经被消费，直接进入下一笔交易输出
                            continue;
                    }
                }
                //交易输出还未被消费，判断这笔输出是否属于指定的address
                //如果一个输出能被一个地址解锁，那么这个输出的资金属于这个地址
                ///改进：可在这里直接保存UTXO，返回
                if(block->transactions[txIndex]->vout[outIndex].canBeUnlockWith(address)){
                    unspentTXS.push_back(block->transactions[txIndex]);
                }
            }//for (int outIndex = 0; outIndex < block->transactions[txIndex]->vout.size(); ++outIndex) {

            //保存已经被消费的交易输出，即包含在其它交易输入的输出
            //不使用conibase，因为它们不解锁输出
            if(!block->transactions[txIndex]->isCoinbase()){
                for (int inIndex = 0; inIndex < block->transactions[txIndex]->vin.size(); ++inIndex) {
                    if(block->transactions[txIndex]->vin[inIndex].canUnlockWith(address)){
                        string inTxID = block->transactions[txIndex]->vin[inIndex].txid;
                        spentTXOs[inTxID].push_back(block->transactions[txIndex]->vin[inIndex].vout);
                    }
                }
            }

        }//for (int txIndex = 0; txIndex < block->transactions.size(); ++txIndex)

        if(block->prevBlockHash=="")
            break;
    }
    return unspentTXS;
}

///改进：findUnspentTransactions函数在查找过程中已经找到UTXO，可直接保存返回
///没必要先保存交易，再在交易中查找UTXO
std::vector<TXOutput*> Blockchain::findUTXO(std::string address) {
    vector<TXOutput*> UTXOs;
    vector<Transaction*> unspentTransactions = this->findUnspentTransactions(address);
    for(auto& tx : unspentTransactions){
        for(auto out : tx->vout){
            if(out.canBeUnlockWith(address))
                UTXOs.push_back(&out);
        }
    }
    return UTXOs;
}

void Blockchain::getBalance(std::string address) {
    int balance = 0;
    vector<TXOutput*> UTXOs = this->findUTXO(address);
    for(TXOutput* out : UTXOs){
        balance += out->value;
    }
    cout << "Balance of " << address << ":" << balance << endl;
}