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
    : _size ( depth ),
      _lineIndex ( 0 ),
      _level ( depth ),
      _stackPointer ( new Result * [depth] )
{
    for ( int rowIndex = 0; rowIndex < _size; ++rowIndex )
    {
        _stackPointer[rowIndex] = new Result [_size];
    }
}

void MiniMaxOptimizer::makeBranch()
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
bool MiniMaxOptimizer::searchEnd()
{
    const int bound = * ( _stackPointer[_lineIndex] - 1 );
    if ( bound > 0 /*winner strategy has been found before*/ )
    {
        _level = _lineIndex + bound;
    }
    return _lineIndex == _level;
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
    if ( searchEnd() )
    {
        return isWinnerStep ( st );
    }
    makeBranch();
    Generator possibleSteps ( getCurrentCollection() );
    Step nextStep;
    while ( possibleSteps.next ( nextStep ) )
    {
        if ( isWinnerStep ( nextStep ) )
        {
            return Result::Best; // instant death
        }
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
            jumpToParentNode();
            return Result::Best; // instant death
        }
    }
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
