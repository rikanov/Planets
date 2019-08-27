#include "stone.h"

Stone * Stone::WALL = new Stone ( nullptr, nullptr, 0, "WALL" );


Stone::Stone ( const Node* N, const Collection * T, uchr I, const std::string& S ) : _name ( S ),  _index ( I ), _team ( T ), _pNode ( N )
{
    if ( _pNode )
    {
        _pNode->setStone ( this );
    }
}

void Stone::step ( const Node * N ) const
{
    _pNode->setStone ( nullptr );
    _pNode = N;
    _pNode->setStone ( this );
}

const Node * Stone::go ( uchr D ) const
{
    const Node * ret = _pNode->go ( D );
    return ret != _pNode ? ret : nullptr;
}
const Node * Stone::go ( uchr r, uchr c, uchr& token ) const
{
    const Node * ret = nullptr;
    for ( int dir = 0; dir < 8; ++dir )
    {
        const Node * pNode = go ( dir );
        if ( pNode && pNode->getRow() == r && pNode->getCol() == c )
        {
            ret = pNode;
            token = dir + _index * 8;
            break;
        }
    }
    return ret;
}
