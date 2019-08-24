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

#ifndef BOARD_H
#define BOARD_H

#include "generator.h"
#include "sstack.h"

class Board: public StepStack
{
    const Node* _WINNER_SPOT;
private:
    // Board grid [rows+2][columns+2]
    Node ** __theGrid;
    Collection * _collectionOfPlayer;
    Collection * _collectionOfProgram;
    Collection * _currentOpponent;

    const int _rows;
    const int _cols;

    int _lastDepth = 0;
public:
    Board ( const int& size = 5 );
    virtual ~Board();
    void reset();
    void show() const;
    bool isPlayerTurn() const;
    bool getStep ( uchr, Step& );
    const Collection * getProgramCollection() const;
    const Collection * getPlayerCollection() const;
    const Collection * getCurrentCollection() const;
    bool isWinnerStep ( const Step& );
    void swapPlayers();
    bool isFinished() const;
};

#endif // BOARD_H
