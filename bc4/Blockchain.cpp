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

std::vector<Transaction> Blockchain::findUnspentTransactions(std::string address) {
    BlockchainItr* bci = new BlockchainItr(this);
    vector<Transaction> unspentTXS;  //包含未消费输出的交易
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
                    unspentTXS.push_back(*(block->transactions[txIndex]));
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
std::vector<TXOutput> Blockchain::findUTXO(std::string address) {
    vector<TXOutput> UTXOs;
    vector<Transaction> unspentTransactions = this->findUnspentTransactions(address);
    for(auto& tx : unspentTransactions){
        for(auto out : tx.vout){
            if(out.canBeUnlockWith(address))
                UTXOs.push_back(out);
        }
    }
    return UTXOs;
}

///UTXOs内容正确，读取出就变成随机数？？？？
void Blockchain::getBalance(std::string address) {
    int balance = 0;
    vector<TXOutput> UTXOs = this->findUTXO(address);
    for(TXOutput out : UTXOs){
        balance += out.value;
    }
    cout << "Balance of " << address << ":" << balance << endl;
}

/**
 * 获取可用于转账的交易输出
 * @param address 转账的转出地址
 * @param mount 转账金额
 * @param spendableOutputs 交易输出集，通过引用当作返回值
 * @return 交易输出的value总和，若比mount小，则表明资金不够
 */
int Blockchain::findSpendableOutputs(std::string address, int amount,
                                     std::map<std::string, std::vector<int>>& spendableOutputs) {
    spendableOutputs.clear();
    vector<Transaction> unspentTXs = this->findUnspentTransactions(address);
    int accumulated = 0;
    for(auto& tx : unspentTXs){
        string txID = tx.id;
        for (int outIndex = 0; outIndex < tx.vout.size(); ++outIndex) {
            if(tx.vout[outIndex].canBeUnlockWith(address)){
                accumulated += tx.vout[outIndex].value;
                spendableOutputs[txID].push_back(outIndex);

                if(accumulated >= amount)  //有足够的数量就不需要继续查找
                    break;
            }
        }
    }
    return accumulated;
}


Transaction* Blockchain::createUTXOTransaction(std::string from,std::string to,int amount){
    vector<TXInput> inputs;
    vector<TXOutput> outputs;
    map<string,vector<int>> spentableOutputs;
    int acc = this->findSpendableOutputs(from,amount,spentableOutputs);

    if(acc < amount){
        cerr << "ERROR:Not enough funds!" << endl;
        return nullptr;
    }

    map<string,vector<int>>::iterator itr = spentableOutputs.begin();
    for(;itr!=spentableOutputs.end();itr++){
        for(auto& out : itr->second){  //对每笔交易输出创建对应的交易输入引用
            TXInput input = TXInput{itr->first,out,from};
            inputs.push_back(input);
        }
    }

    //创建两个交易输出
    //输出到目的账户
    //多余的输出返回到原账户
    TXOutput output = TXOutput{amount,to};
    outputs.push_back(output);
    if(acc > amount){
        TXOutput newOut = TXOutput{acc-amount,from};
        outputs.push_back(newOut);
    }

    Transaction* tx = new Transaction{"",inputs,outputs};
    tx->setId();

    return tx;
}

void Blockchain::send(std::string from,std::string to,int amount){
    Transaction* tx = this->createUTXOTransaction(from,to,amount);
    if(!tx){
        cerr << "ERROR:Send Transaction failed!" << endl;
        return;
    }
    ///这里没有实现内存池，发生一笔交易时，就直接把这笔交易打包成一个区块
    ///即一个区块只包含一笔交易
    vector<Transaction*> transactions;
    transactions.push_back(tx);
    this->addBlock(transactions);
    cout << "Send Transaction success!" << endl;
}