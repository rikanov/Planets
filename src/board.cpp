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

Board::Board(const int& S)
    :_rows(S + 2)
    ,_cols(S)
    ,_collectionOfPlayer(nullptr)
    ,_collectionOfProgram(nullptr)
{
    // --- Create grid --- //
    // allocate size
    __theGrid = new Node*[_rows + 2];
    for (int row = 0; row < _rows + 2; ++row)
    {
        __theGrid[row] = new Node[_cols + 2];
    }
    // set borders -> vertical
    for (int id = 0; id < _cols + 2; ++id)
    {
        __theGrid[0][id].setStone(Stone::WALL);
        __theGrid[_rows + 1][id].setStone(Stone::WALL);
    }
    // set borders -> horizontal
    for (int id = 0; id < _rows + 2; ++id)
    {
        __theGrid[id][_cols + 1].setStone(Stone::WALL);
        __theGrid[id][0].setStone(Stone::WALL);
    }
    // set auxiliary parameters and make topology
    for (int row = 1; row < _rows + 1; ++row)
    {
        for (int col = 1; col < _cols + 1; ++col)
        {
            __theGrid[row][col].setPos(row,col);
            Node & toSet = __theGrid[row][col];
            for (int dir = 0; dir < 8; ++dir)
            {
                const int ver = (dir == 7 || dir < 2) - (2 < dir && dir < 6);
                const int hor = (0 < dir && dir < 4) - (4 < dir);
                toSet.connect( &__theGrid[row + ver][col + hor], dir);
            }
        }
    }
    // set the middle field of the board as the place of victory
    _WINNER_SPOT = &__theGrid[(_rows + 1) / 2][(_cols + 1) / 2];
    // --------------- //
}
void Board::reset()
{
    for (int row = 1; row < _rows + 1; ++row)
    {
        for (int col = 1; col < _cols + 1; ++col)
        {
            __theGrid[row][col].setStone(nullptr);
        }
    }

    delete _collectionOfPlayer;
    delete _collectionOfPlayer;

    _collectionOfPlayer = new Collection(YOURS, &__theGrid[1][1]);
    _collectionOfProgram = new Collection(MINE, &__theGrid[_rows][1]);
    resetStack();
}
static inline void NL() {
    std::cout << std::endl << '|';
}

void Board::show() const
{
    const char* separator = "---- ";
    const char* empty = "    |";
    for (int row = _rows; row > 0; --row)
    {
        NL();
        for (int col = 1; col <= _cols; ++col)
        {
            std::cout << separator;
        }
        NL();
        for (int col = 1; col <= _cols; ++col)
        {
            const Node *field = &(__theGrid[row][col]);
            std::string name = field->getName();
            if (field == _WINNER_SPOT && name.empty())
            {
                std::cout << " () |";
                continue;
            }
            else if (name.empty())
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
    for (int col = 1; col <= _cols; ++col)
    {
        std::cout << separator;
    }
    NL();
}

Board::~Board()
{
    for (int i = 0; i < _rows + 2; ++i)
    {
        delete[] __theGrid[i];
    }
    delete[] __theGrid;
    delete _collectionOfPlayer;
    delete _collectionOfProgram;
}

