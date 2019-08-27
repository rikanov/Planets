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

public:
    Board ( const int& size = 5 );
    virtual ~Board();
    void reset();
    void show() const;
    bool isPlayerTurn() const;
    bool getStep ( uchr, Step& ) const;
    bool getStep ( uchr, uchr, Step& ) const;
    bool getStep ( uchr, uchr, uchr, uchr, Step& ) const;
    const Collection * getProgramCollection() const;
    const Collection * getPlayerCollection() const;
    const Collection * getCurrentCollection() const;
    bool isWinnerStep ( const Step& );
    void swapPlayers();
    bool isFinished() const;
};

#endif // BOARD_H
