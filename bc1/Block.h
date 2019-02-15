//
// Created by zjp on 19-2-14.
//

#ifndef BLOCKCHAINCPP_BLOCK_H
#define BLOCKCHAINCPP_BLOCK_H

#include <string>


class Block{
public:
    std::string sPrevHash;   //上一区块的哈希
    Block(uint32_t nIndexIn, const std::string &sDataIn);
    std::string GetHash();
    void MineBlock(uint32_t nDifficulty);  //挖矿函数

private:
    uint32_t _nIndex; //该区块的索引值
    int64_t _nNonce;  //区块随机数，用于哈希值的产生
    std::string _sData;  //区块描述字符
    std::string _sHash; //区块哈系值
    time_t _createTime;  //创建时间
    std::string _calculateHash() const; //哈希值计算函数
};

#endif //BLOCKCHAINCPP_BLOCK_H
