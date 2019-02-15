//
// Created by zjp on 19-2-15.
//

#include "ProofofWork.h"
#include "../utils/sha256.h"
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

ProofofWork::ProofofWork(Block *b) {
    block = b;
    //difficultNum = DIFFICULTY_NUM;
}

/**
 * 生成待计算hash的数据
 * @param nonce
 * @return
 */
std::string ProofofWork::calculateHash(int64_t nonce) {
    stringstream ss;
    ss << block->prevBlockHash << this->hashTransactions() << block->timeStamp << nonce;
    return sha256(ss.str());
}

std::string ProofofWork::hashTransactions() {
    stringstream ss;
    for (int i = 0; i < block->transactions.size(); ++i) {
        ss << block->transactions[i]->id;
    }
    string hash = sha256(ss.str());
    return hash;
}

/**
 * 开始运行哈希碰撞
 * 寻找符合条件的哈希值
 * @param hash 符合条件的hash会通过参数引用返回
 * @return nonce
 */
int64_t ProofofWork::run(std::string &hash) {
    int64_t nonce = 0;
    //cout << "Mining the block containing " << block->data << endl;
    cout << "Mining block ......" << endl;

    while(nonce<numeric_limits<int64_t>::max()){
        hash = calculateHash(nonce);

        char cstr[DIFFICULTY_NUM+1];
        for (uint32_t i = 0; i < DIFFICULTY_NUM; ++i) {
            cstr[i] = '0';
        }
        cstr[DIFFICULTY_NUM] = '\0';
        string str(cstr);

        if(hash.substr(0,DIFFICULTY_NUM)==str)
            break;
        else
            nonce++;
    }
    return nonce;
}

/**
 * 验证区块的有效性
 * @return
 */
bool ProofofWork::validate() {
    string hash = calculateHash(block->nonce);

    char cstr[DIFFICULTY_NUM+1];
    for(uint32_t i=0;i<DIFFICULTY_NUM;i++)
        cstr[i] = '0';
    cstr[DIFFICULTY_NUM] = '\0';
    string str(cstr);
    return (hash.substr(0,DIFFICULTY_NUM)==str);
}