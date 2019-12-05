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

#include "global.h"
#include "minimaxoptimizer.h"

MiniMaxOptimizer::MiniMaxOptimizer ( const int & depth )
    : _lineIndex ( 0 ),
      _maximumLevel ( depth ),
      _stackPointer ( new Result * [depth] )
{
    for ( int rowIndex = 0; rowIndex < _size; ++rowIndex )
    {
        _stackPointer[rowIndex] = new Result [_size];
    }
}

void MiniMaxOptimizer::createBranch()
{
    * ( ++_stackPointer[++_lineIndex] ) = Result::Best;
    for ( int next = _lineIndex + 1; next < _level ; ++next )
    {
        Result toClone = * ( _stackPointer[next] );
        * ( ++_stackPointer[next] ) = toClone;
    }
}

void MiniMaxOptimizer::removeBranch()
{
    for ( int next = _lineIndex  + 1; next <_level; ++next )
    {
        --_stackPointer[next];
    }
}

void MiniMaxOptimizer::updateBranch()
{
    for ( int next = _lineIndex + 1; next < _level ; ++next )
    {
        const Result toClone = * ( _stackPointer[next] );
        * ( --_stackPointer[next] ) = toClone;
    }
}

MiniMaxOptimizer::UpdateResult MiniMaxOptimizer::checkForUpdate ( const Result& R )
{
    if ( ! ( _stackPointer[_lineIndex] - 1 )->worseThan ( R ) )
    {
        return INTERRUPTED;
    }
    if ( R.worseThan ( *_stackPointer[_lineIndex] ) )
    {
        lineEnd() = R;
        return UPDATED;
    }
    return SKIPPED;
}

Result MiniMaxOptimizer::test ( const Step& st )
{
    storeStep( st );
    Generator possibleSteps ( getCurrentCollection() );
    Step nextStep;
    while ( possibleSteps.next ( nextStep ) )
    {
        if ( isWinnerStep ( nextStep ) )
        {
            return Result::Best; // message to the sender: instant death is waiting here for you
        }
        if ( searchEnded() )
        {
            continue;
        }
        createBranch();
        const Result next = test ( nextStep );
        switch ( checkForUpdate ( next ) )
        {
        case SKIPPED:
            removeBranch();
            break;
        case UPDATED:
            updateBranch();
            break;
        default: // INTERRUPTED
            removeBranch();
            undoStep();
            jumpToParentNode();
            return Result::Best; // message to the sender: do not choose a worse option than that you have already found!
        }
    }
    undoStep();
    jumpToParentNode();
    return lastFound();
}

MiniMaxOptimizer::~MiniMaxOptimizer()
{
    for ( int rowIndex = 0; rowIndex < _size; ++rowIndex )
    {
        delete[] _stackPointer[rowIndex];
    }
    delete[] _stackPointer;
}
