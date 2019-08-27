#ifndef ENGINE_HEADER__H
#define ENGINE_HEADER__H
#include "board.h"
#include "result.h"
#include "cache.h"

class Engine: public Board
{
private:

    Cache _cache;

    int _currentLevel;
    int _boundLevel;
    int _deepSearchLevel;

    inline Result seeker ( Step&, Result& );
    Result test0();
    Result test0_();
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
