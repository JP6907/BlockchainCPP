//
// Created by zjp on 19-2-15.
//

#ifndef BLOCKCHAINCPP_BLOCK_H
#define BLOCKCHAINCPP_BLOCK_H

#include <string>

#define DIFFICULTY_NUM 4

class Block{
public:
    time_t timeStamp;
    std::string data;
    std::string prevBlockHash;
    std::string hash;
    int64_t nonce;

    std::string Serialize(Block* b);
    static Block* NewBlock(std::string data,std::string prevBlockHash);
    static Block* DeserializeBlock(std::string d);

    static Block* NewGenesisBlock();

private:
    Block(std::string data,std::string prevBlockHash);
};


#endif //BLOCKCHAINCPP_BLOCK_H
