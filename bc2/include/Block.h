//
// Created by zjp on 19-2-14.
//

#ifndef BLOCKCHAINCPP_BLOCK_H
#define BLOCKCHAINCPP_BLOCK_H

#include <string>

class Block{
public:
    std::string _hash;  //当前区块hash值
    std::string _data;  //区块描述字符
    std::string _prevHash; //记录上一个区块的hash值

    Block(const std::string &dataIn,const std::string &prevHash);
    std::string CalaulateHash();  //计算本区块的可能hash，返回值在MineBlock函数中验证
    void ProofOfWork(int difficulty);

private:
    int64_t _nNonce;  //区块随机数，用于hash值的产生
    time_t _tTime;  //区块创建时间
};

#endif //BLOCKCHAINCPP_BLOCK_H
