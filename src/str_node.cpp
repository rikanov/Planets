#include "stone.h"

const Node * Node::go ( const uint8_t& dir ) const
{
    return __next[dir]->isEmpty() ? __next[dir]->go ( dir ) : this;
}

std::string Node::getName() const
{
    return _pStone ? _pStone->getName() : "";
}
