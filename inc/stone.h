#ifndef STONE_HEADER__H
#define STONE_HEADER__H

#include "step.h"

class Collection;
class Stone
{
    std::string _name; // for basic ui only
    uchr _index;
    const Collection * _team;
    mutable const Node * _pNode;
public:
    Stone ( const Node* N, const Collection * T, uchr I, const std::string& S ) ;
    const Node * go ( uchr D ) const;
    const Node * go ( uchr r, uchr c, uchr& token ) const;
    void step ( const Node* ) const;
    const Node* getNode() const
    {
        return _pNode;
    }
    const Collection * getTeam() const
    {
        return _team;
    }
    std::string getName() const
    {
        return _name;
    }
    static Stone * WALL;
};

#endif
