#ifndef ENGINE_HEADER__H
#define ENGINE_HEADER__H
#include "board.h"
#include "result.h"

class Engine: public Board
{
private:
    int _currentLevel;
    int _boundLevel;

    Result test0();
    Result test ( Result& search_bound );
protected:
public:
    Engine();
    void setBoundLevel ( const int& BL )
    {
        _boundLevel = BL;
    }
    void makeStep ( uchr );
    void makeStep ( uchr, uchr );
    Result getResult();
};
#endif
