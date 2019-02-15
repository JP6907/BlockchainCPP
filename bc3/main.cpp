#include <iostream>
#include "BlockchainItr.h"
#include "Blockchain.h"

using namespace std;

void printChain(Blockchain* bc){
    BlockchainItr* bci = new BlockchainItr(bc);
    while(1){
        Block* block = bci->nextBlock();
        cout << "Prev hash: " << block->prevBlockHash << endl;
        cout << "Data: " << block->data << endl;
        cout << "Hash: " << block->hash << endl;

        if(block->prevBlockHash=="")  //到达创世区块
            break;
    }
}

int main() {
    Blockchain* bc = Blockchain::NewBlockchain();
    cout << endl;
    printChain(bc);
    cout << "----------------" << endl;

    bc->addBlock("Send 1 BTC to Ivan");
    cout << endl;
    printChain(bc);
    cout << "----------------" << endl;

    bc->addBlock("Pay 0.1102 BTC for a coffee");
    cout << endl;
    printChain(bc);
    cout << "----------------" << endl;

    return 0;
}