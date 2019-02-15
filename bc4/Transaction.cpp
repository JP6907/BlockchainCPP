//
// Created by zjp on 19-2-15.
//
#include "Transaction.h"
#include "../utils/sha256.h"
#include <sstream>

using namespace std;


/**
 * 创建新的Coinbase交易
 * Coinbase交易只有输出没有输入
 * 当矿工挖出一个新块时，它会向新的块中添加一个coinbase交易
 * 交易的输出用于奖励矿工
 * @param to
 * @param data
 * @return
 */
Transaction* NewCoinbaseTX(std::string to,std::string data){
    if(data == "")
        data = "Reward to " + to;

    TXInput txin = TXInput{"",-1,data};
    TXOutput txout = TXOutput{SUBSIDY,to};
    Transaction* tx = new Transaction();
    tx->vin.push_back(txin);
    tx->vout.push_back(txout);
    tx->setId();

    return tx;
}

/**
 * 生成交易的id
 */
void Transaction::setId() {
    stringstream ss;
    for (int i = 0; i < this->vin.size(); ++i) {
        ss << this->vin[i].txid << this->vin[i].vout << this->vin[i].scriptSig;
    }
    for (int j = 0; j < this->vout.size(); ++j) {
        ss << this->vout[j].value << this->vout[j].scriptPubkey;
    }
    this->id = sha256(ss.str());
}

bool Transaction::isCoinbase() {
    return this->vin.size()==1 && this->vin[0].txid=="" && this->vin[0].vout==-1;
}

bool TXInput::canUnlockWith(std::string unlockingData) {
    return this->scriptSig == unlockingData;
}

bool TXOutput::canBeUnlockWith(std::string unlockingData) {
    return this->scriptPubkey == unlockingData;
}
