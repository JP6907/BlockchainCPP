//
// Created by zjp on 19-2-15.
//
#include "Blockchain.h"
#include "BlockchainItr.h"
#include <iostream>

using namespace std;

void printChain(Blockchain* bc){
    BlockchainItr* bci = new BlockchainItr(bc);
    while(1){
        Block* block = bci->nextBlock();
        cout << "Prev hash: " << block->prevBlockHash << endl;
        cout << "Transactions num: " <<block->transactions.size() << endl;
        //打印当前区块包含的每笔交易的输入和输出
        for (int i = 0; i < block->transactions.size(); ++i) {
            cout << "  Transaction" << i << " in:" << endl;
            for (int j = 0; j < block->transactions[i]->vin.size(); ++j) {
                cout << "    " << block->transactions[i]->vin[j].scriptSig << endl;
            }
            cout << "  Transaction" << i << " out:" << endl;
            for (int k = 0; k < block->transactions[i]->vout.size(); ++k) {
                cout << "    " << block->transactions[i]->vout[k].scriptPubkey << endl;
            }
        }
        cout << "Hash: " << block->hash << endl;

        if(block->prevBlockHash=="")  //到达创世区块
            break;
    }
}

int main(){
    Blockchain* bc = Blockchain::NewBlockchain("def");
    printChain(bc);
    bc->getBalance("def");
    bc->getBalance("noName");

    return 0;
}