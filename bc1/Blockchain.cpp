//
// Created by zjp on 19-2-14.
//

#include "Blockchain.h"

Blockchain::Blockchain() {
    _vChain.emplace_back(Block(0,"Genesis Block"));
    _nDifficulty = DIFFICULTY_NUM;
}

void Blockchain::addBlock(Block bNew) {
    bNew.sPrevHash = _getLastBlock().GetHash();
    bNew.MineBlock(_nDifficulty);
    _vChain.push_back(bNew);
}

Block Blockchain::_getLastBlock() const {
    return _vChain.back();
}