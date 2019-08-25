#ifndef STRUCT_NODE_H
#define STRUCT_NODE_H

#include "global.h"

class Stone;
class Node
{
    Node* __next[8] = {};
    mutable const Stone * _pStone = nullptr;
    int _row = 0, _col = 0;
public:
    const Node * go ( const uchr& ) const;
    void connect ( Node* N, const uchr& D )
    {
        __next[D] = N;
    }
    const Stone * getStone() const
    {
        return _pStone;
    }
    void setStone ( const Stone * S ) const
    {
        _pStone = S;
    }
    void setPos ( uchr R, uchr C )
    {
        _row = R;
        _col = C;
    }
    bool isEmpty() const
    {
        return _pStone == nullptr;
    }
    const Node * next ( uchr U ) const
    {
        return __next[U];
    }
    std::string getName() const;
    bool operator == ( const Node& N ) const
    {
        return _row == N._row && _col == N._col;
    }
    bool operator != ( const Node& N ) const
    {
        return _row != N._row || _col != N._col;
    }

};

#endif
