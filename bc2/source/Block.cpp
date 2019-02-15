//
// Created by zjp on 19-2-14.
//
#include <time.h>
#include "../include/Block.h"
#include <sstream>
#include <iostream>
#include "../../utils/sha256.h"

using namespace std;

Block::Block(const std::string &dataIn,const std::string &prevHash) {
    _tTime = time(nullptr);
    _nNonce = 0;
    _data = dataIn;
    _prevHash = prevHash;
}

//创建一个区块就是根据创建时间、描述字符、区块随机数字等数据来计算出一个哈希值
//_tTime、_data、_prevHash是不变的
//唯一变化的是nNonce的值，nNonce的变化会产生不同的hash值
std::string Block::CalaulateHash() {
    stringstream ss;
    ss << _tTime << _data << _prevHash << _nNonce;
    return sha256(ss.str());
}

void Block::ProofOfWork(int difficulty) {
    char cstr[difficulty+1];
    for (uint32_t i = 0; i < difficulty; ++i) {
        cstr[i] = '0';
    }
    cstr[difficulty] = '\0';
    string str(cstr);
    do{
        _nNonce++;
        _hash = CalaulateHash();
    }while(_hash.substr(0,difficulty)!=str);

    std::cout << "Block mined: " << _hash << std::endl;
    cout << "nNonce: " << _nNonce << endl;
}