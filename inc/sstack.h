#ifndef SSTACK_HEADER__H
#define SSTACK_HEADER__H

#include "stone.h"
#include "datacache.h"

class StepStack
{
protected:
    DataCache _cache;
    const int _stackSize;
    std::ofstream _outfile[3];
    // Store steps for UI (undo, redo)
    Step * __moveHistory,*_currentMove,*_lastMove;

public:
    StepStack ( const int& S = MAX_NUMBER_OF_MOVES );
    virtual ~StepStack();
    void saveStack ( int, int );
    bool isStarted() const
    {
        return _currentMove != __moveHistory + 1;
    }
    bool isTheLastMove() const
    {
        return _currentMove == _lastMove;
    }
    int stepCount() const
    {
        return ( _currentMove - __moveHistory - 1 );
    }
    const Step& moveHistory ( const int& index ) const
    {
        return index < 0 ? * ( _currentMove + index + 1 ) : __moveHistory[index];
    }
    bool fromChache ( Result& R ) const;
    void resetStack();
    void storeStep ( Step S );
    void undoStep();
    void redoStep();
    bool isLoop() const;
};

#endif
