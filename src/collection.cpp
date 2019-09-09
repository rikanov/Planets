#include "collection.h"

Collection::Collection ( Opponent T, const Node * S, uint8_t size )
  :_size(size)
{
    __collection = new Stone * [_size + 1];
    __collection[5] = nullptr;
    Stone ** pNext = __collection;
    std::string name = T == MINE ? "A" : "X";
    for ( uint8_t id = 0; id < _size; ++id )
    {
        std::string next = name;
        next.push_back ( id + '1' );
        * ( pNext++ ) = new Stone ( S, this, id, next );
        S = S->next ( 2 ); // step right to get the next field
    }
}

bool Collection::getStep ( uint8_t ID, Step& S ) const
{
    return getStep ( ID / 8, ID % 8, S );
}

bool Collection::getStep ( uint8_t ID, uint8_t dir, Step& S ) const
{
    bool ret = false;
    const Stone* pStone = __collection[ID ];
    const Node* pNode = pStone->go ( dir );
    if ( pNode != nullptr )
    {
        S.set ( pStone,pNode );
        S.setToken ( dir + ID * 8 );
        ret = true;
    }
    return ret;
}

bool Collection::getStep ( const Stone * pStone, uint8_t r, uint8_t c, Step& S ) const
{
    bool ret = false;
    if ( pStone->getTeam() == this )
    {
        uint8_t token;
        const Node * pNode = pStone->go ( r, c, token );
        ret = ( pNode != nullptr );
        S.set ( pStone, pNode );
        S.setToken ( token );
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
