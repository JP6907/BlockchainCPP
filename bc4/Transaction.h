//
// Created by zjp on 19-2-15.
//

#ifndef BLOCKCHAINCPP_TRANSACTION_H
#define BLOCKCHAINCPP_TRANSACTION_H

#define SUBSIDY 10  //挖矿奖励

#include <string>
#include <vector>
//#include "Blockchain.h"

/**
 * 交易输出
 */
typedef struct txoutput{
    int value;
    std::string scriptPubkey;  //锁定脚本
    //判断输出的资金能够被解锁，需提供解锁脚本
    bool canBeUnlockWith(std::string unlockingData);
}TXOutput;

/**
 * 交易输入
 */
typedef struct txinput{
    std::string txid;  //输入来源交易id
    int vout;   //引用的交易的输出编号
    std::string scriptSig;  //解锁脚本
    //判断能够解锁输入交易的锁定脚本
    bool canUnlockWith(std::string unlockingData);
}TXInput;

/**
 * 交易
 */
typedef struct transaction{
    std::string id;  //交易id
    std::vector<TXInput> vin;
    std::vector<TXOutput> vout;

    void setId();
    //判断是否coinbase交易
    bool isCoinbase();
}Transaction;


Transaction* NewCoinbaseTX(std::string to,std::string data);


#endif //BLOCKCHAINCPP_TRANSACTION_H
