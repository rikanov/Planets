#include "stone.h"

Stone * Stone::WALL = new Stone ( nullptr,"WALL" );


void Stone::step ( const Node * N ) const
{
    _pNode->setStone ( nullptr );
    _pNode = N;
    _pNode->setStone ( this );
}
