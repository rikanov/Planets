#include "collection.h"

Collection::Collection ( Turn T, const Node * S )
{
    __collection = new Stone * [6];
    __collection[5] = nullptr;
    Stone ** pNext = __collection;
    std::string name = T == MINE ? "A" : "X";
    for ( int id = 0; id < 5; ++id )
    {
        std::string next = name;
        next.push_back ( id + '1' );
        * ( pNext++ ) = new Stone ( S, next );
        S = S->next ( 2 ); // step right to get the next field
    }
}

bool Collection::getStep ( uchr ID, Step& S ) const
{
    return getStep ( ID / 8, ID % 8, S );
}

bool Collection::getStep ( uchr ID, uchr dir, Step& S ) const
{
    bool ret = false;
    const Stone* pStone = __collection[ID ];
    const Node* pNode = pStone->go ( dir );
    if ( pNode != nullptr )
    {
        S.set ( pStone,pNode );
        ret = true;
    }
    return ret;
}

Collection::~Collection()
{
    for ( Stone ** pNext = __collection; *pNext; ++pNext )
    {
        delete *pNext;
    }
    delete __collection;
}
