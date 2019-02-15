#include <iostream>
#include "Blockchain.h"
#include "Blockchain_Interface.h"

using namespace std;

int main() {
    Blockchain* bc = BC_Interface::NewBlockchain();

    bc->AddBlock("Send 1 BTC to Ivan");
    bc->AddBlock("Send 2 more BTC to Ivan");

    for(int i=0;i<bc->blocks.size();i++){
        std::cout << "Prev hash = " << bc->blocks[i]->_prevHash << std::endl;
        std::cout << "data  = " << bc->blocks[i]->_data << std::endl;
        std::cout << "hash  = " << bc->blocks[i]->_hash << std::endl << std::endl;
    }

    delete bc;

    return 0;
}