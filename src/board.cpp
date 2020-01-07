/*
 * BlackHole -- a simple abstract board game designed by myself
 * Copyright (C) 2019  Robert Ikanov, robert.ikanov@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "board.h"
#include "string"

Board::Board ( const int& S )
    :_rows ( S + 2 )
    ,_cols ( S )
    ,_collectionOfPlayer ( nullptr )
    ,_collectionOfProgram ( nullptr )
{
    // --- Create grid --- //
    // allocate size
    __theGrid = new Node*[_rows + 2];
    for ( uint8_t row = 0; row < _rows + 2; ++row )
    {
        __theGrid[row] = new Node[_cols + 2];
    }
    // set borders -> vertical
    for ( uint8_t id = 0; id < _cols + 2; ++id )
    {
        __theGrid[0][id].setStone ( Stone::WALL );
        __theGrid[_rows + 1][id].setStone ( Stone::WALL );
    }
    // set borders -> horizontal
    for ( uint8_t id = 0; id < _rows + 2; ++id )
    {
        __theGrid[id][_cols + 1].setStone ( Stone::WALL );
        __theGrid[id][0].setStone ( Stone::WALL );
    }
    // set auxiliary parameters and make topology
    for ( uint8_t row = 1; row < _rows + 1; ++row )
    {
        for ( uint8_t col = 1; col < _cols + 1; ++col )
        {
            __theGrid[row][col].setPos ( row,col );
            Node & toSet = __theGrid[row][col];
            for ( uint8_t dir = 0; dir < 8; ++dir )
            {
                const int ver = ( dir == 7 || dir < 2 ) - ( 2 < dir && dir < 6 );
                const int hor = ( 0 < dir && dir < 4 ) - ( 4 < dir );
                toSet.connect ( &__theGrid[row + ver][col + hor], dir );
            }
        }
    }
    // set the middle field of the board as the place of victory
    _WINNER_SPOT = &__theGrid[ ( _rows + 1 ) / 2][ ( _cols + 1 ) / 2];
    // --------------- //
}
void Board::reset()
{
    for ( uint8_t row = 1; row < _rows + 1; ++row )
    {
        for ( uint8_t col = 1; col < _cols + 1; ++col )
        {
            __theGrid[row][col].setStone ( nullptr );
        }
    }

    delete _collectionOfPlayer;
    delete _collectionOfProgram;

    _collectionOfPlayer = new Collection ( YOURS, &__theGrid[1][1], _cols /*size*/ );
    _collectionOfProgram = new Collection ( MINE, &__theGrid[_rows][1], _cols /*size*/ );
    _currentOpponent = _collectionOfPlayer;
    resetStack();
}
static inline void NL()
{
    std::cout << std::endl << '|';
}

void Board::show() const
{
    const char* separator = "---- ";
    const char* empty = "    |";
    for ( uint8_t row = _rows; row > 0; --row )
    {
        NL();
        for ( uint8_t col = 1; col <= _cols; ++col )
        {
            std::cout << separator;
        }
        NL();
        for ( uint8_t col = 1; col <= _cols; ++col )
        {
            const Node *field = & ( __theGrid[row][col] );
            std::string name = field->getName();
            if ( field == _WINNER_SPOT && name.empty() )
            {
                std::cout << " () |";
                continue;
            }
            else if ( name.empty() )
            {
                std::cout << empty;
            }
            else
            {
                std::cout << " " << name << " |";
            }
        }
    }
    NL();
    for ( uint8_t col = 1; col <= _cols; ++col )
    {
        std::cout << separator;
    }
    NL();
}

bool Board::isPlayerTurn() const
{
    return _currentOpponent == _collectionOfPlayer;
}

const Collection * Board::getPlayerCollection() const
{
    return _collectionOfPlayer;
}

const Collection * Board::getProgramCollection() const
{
    return _collectionOfProgram;
}

const Collection * Board::getCurrentCollection() const
{
    return _currentOpponent;
}

bool Board::getStep ( uint8_t token, Step& S ) const
{
    return _currentOpponent->getStep ( token, S );
}

bool Board::getStep ( uint8_t ID, uint8_t dir, Step& S ) const
{
    return _currentOpponent->getStep ( ID, dir, S );
}

bool Board::getStep ( uint8_t r1, uint8_t c1, uint8_t r2, uint8_t c2, Step& S ) const
{
    return _currentOpponent->getStep ( __theGrid[r1][ c1].getStone(), r2, c2, S );
}

bool Board::getStep ( uint8_t ID, uint8_t row, uint8_t col, Step& S ) const
{
    bool ret = false;
    for ( uint8_t dir = 0; dir < 8; ++dir )
    {
        if ( _currentOpponent->getStep ( ID, dir, S ) && S.aim() == & __theGrid[row][col] )
        {
            ret = true;
            break;
        }
    }
    return ret;
}

void Board::initCache()
{
    for ( int centerID = 0, c = -1; c <= 1; ++c )
    {
        for ( int r = -1; r <= 1; ++r )
        {
            if ( c || r )
            {
                _centerNodes [ centerID] = &__theGrid [ ( _rows + 1 ) / 2 + r][ ( _cols + 1 ) / 2 + c];
                int index = 0, col = ( _cols + 1 ) / 2, row = ( _rows + 1 ) / 2 ;
                do
                {
                    col-=c;
                    row -=r;
                    _treatingNodes[centerID][index++] = &__theGrid[row][col];
                }
                while ( __theGrid[row][col].getStone() != Stone::WALL );
            }
        }
    }
}

bool Board::isWinnerStep ( const Step & S )
{
    return S.aim() == _WINNER_SPOT;
}

void Board::swapPlayers()
{
    _currentOpponent = ( _currentOpponent == _collectionOfProgram ) ? _collectionOfPlayer : _collectionOfProgram;
}

bool Board::isFinished() const
{
    return _WINNER_SPOT->getStone() != nullptr;
}

Board::~Board()
{
    for ( uint8_t i = 0; i < _rows + 2; ++i )
    {
        delete[] __theGrid[i];
    }
    delete[] __theGrid;
    delete _collectionOfPlayer;
    delete _collectionOfProgram;
}

