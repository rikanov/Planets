#include "stone.h"

const Node * Node::go(const uchr& dir) const
{
    return __next[dir]->isEmpty() ? __next[dir]->go(dir) : this;
}

std::string Node::getName() const {
    return _pStone ? _pStone->getName() : "";
}
