/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2019  Robert Ikanov <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MINIMAXOPTIMIZED_H
#define MINIMAXOPTIMIZED_H

#include "board.h"
#include "result.h"

class MiniMaxOptimizer: public Board
{
    enum UpdateResult
    {
        INTERRUPTED,
        SKIPPED,
        UPDATED
    };
    int _size;

    Result ** _stackPointer;
    int _lineIndex;
    int _level;

    void makeBranch();
    void removeBranch();
    void updateBranch();
    bool searchEnd();

    UpdateResult checkForUpdate ( const Result& );

    inline void jumpToParentNode()
    {
        --_lineIndex;
    }
    inline Result& lineEnd()
    {
        return * ( _stackPointer[_lineIndex] );
    }
    inline Result lastFound()
    {
        return _stackPointer[_lineIndex]->swap();
    }
    Result test ( const Step& );

public:
    /**
     * Default constructor
     */
    MiniMaxOptimizer ( const int& );
    /**
     * Destructor
     */
    ~MiniMaxOptimizer();

};

#endif // MINIMAXOPTIMIZED_H
