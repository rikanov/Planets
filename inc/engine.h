#ifndef ENGINE_HEADER__H
#define ENGINE_HEADER__H
#include "board.h"
#include "cache.h"

class Engine: public Board
{
private:

    Cache _cache;

    int _currentMaxLevel;
    int _boundLevel;
    int _deepSearchLevel;
    int _checkingLevel = 5;

    int yourTurn ( const int& );
    int myTurn ( const int& );
protected:
public:
    Engine();
    void setDifficulty ( const int& BL )
    {
        _boundLevel = BL;
    }
    Step getBestStep();
};
#endif
