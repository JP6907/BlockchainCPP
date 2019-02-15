//
// Created by zjp on 19-2-14.
//
#include "Block.h"
#include "../utils/sha256.h"
#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

Block::Block(uint32_t nIndexIn, const std::string &sDataIn) : _nIndex(nIndexIn),_sData(sDataIn){
    _nNonce = -1;
    _createTime = time(nullptr);
}

std::string Block::GetHash() {
    return _sHash;
}

void Block::MineBlock(uint32_t nDifficulty) {
    char cstr[nDifficulty +1];
    for(uint32_t i=0;i<nDifficulty;i++){
        cstr[i] = '0';
    }
    cstr[nDifficulty] = '\0';
    string str(cstr);  //DIFFICULTY_NUM个0
    do{
        _nNonce++;
        _sHash = _calculateHash();  //使用不同的_nNonce来进行哈系碰撞，直到产生符合条件的哈希值
    }while(_sHash.substr(0,nDifficulty)!=str); //当产生的哈希值前DIFFICULTY_NUM位为0时，限制了区块产生速度，POW
    cout << "Block mined: " << _sHash << endl;
    cout << "nNonce: " << _nNonce << endl;
}

//创建一个区块就是根据创建时间、描述字符、区块随机数字等数据来计算出一个哈希值
//_nIndex、_createTime、_sData是不变的
//唯一变化的是nNonce的值，nNonce的变化会产生不同的hash值
inline std::string Block::_calculateHash() const {
    stringstream ss;
    ss << _nIndex << _createTime << _sData << _nNonce << sPrevHash;
    return sha256(ss.str());
}
