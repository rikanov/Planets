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
    int _maximumLevel;

    Result ** _stackPointer;
    Result ** _startStackPointer;
    int _lineIndex;

    void createBranch();
    void removeBranch();
    void updateBranch();

    UpdateResult checkForUpdate ( const Result& );


    inline bool searchEnded()
    {
        return _lineIndex == _maximumLevel;
    }
    inline void jumpToParentNode()
    {
        --_lineIndex;
    }
    inline const Result& lineEnd()
    {
        return * ( _stackPointer[_lineIndex] );
    }
    inline void setLineEnd ( const Result& R )
    {
        * ( _stackPointer[_lineIndex] ) = R;
    }
    inline Result lastFound()
    {
        return _stackPointer[_lineIndex]->swap();
    }
    Result test ( const Step& );
    Result test_0 ();

public:
    /**
     * Default constructor
     */
    MiniMaxOptimizer ( const int& depth = 10);
    /**
     * Destructor
     */
    ~MiniMaxOptimizer();

    void setBoundLevel ( const int& BL )
    {
        _maximumLevel = BL;
    }
    Result getResult();
};

#endif // MINIMAXOPTIMIZED_H
