#ifndef SSTACK_HEADER__H
#define SSTACK_HEADER__H

#include "stone.h"

class StepStack
{
protected:
    const int _stackSize;
    // Store steps for UI (undo, redo)
    Step * __moveHistory,*_currentMove,*_lastMove;

public:
    StepStack ( const int& S = MAX_NUMBER_OF_MOVES );
    virtual ~StepStack();
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
    void resetStack();
    void storeStep ( Step S );
    void undoStep();
    void redoStep();
    bool isLoop() const;
};

#endif
