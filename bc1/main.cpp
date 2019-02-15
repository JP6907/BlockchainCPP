#include <iostream>
#include "Blockchain.h"

using namespace std;

int main() {
    Blockchain *bc = new Blockchain();
    cout << "Mine block1 ..." << endl;
    bc->addBlock(Block(1,"Block1 Data"));
    cout << "Mine block2 ..." << endl;
    bc->addBlock(Block(2,"Block2 Data"));
    cout << "Mine block3 ..." << endl;
    bc->addBlock(Block(3,"Block1 Data"));

    return 0;
}