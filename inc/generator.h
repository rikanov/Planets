#ifndef GENERATOR_HEADER__H
#define GENERATOR_HEADER__H

#include "collection.h"

class Generator
{
    const Collection * _coll;
    uchr * __permute;
    uchr _stepID;

public:
    Generator ( const Collection * C,const bool& shuffle = false );
    ~Generator();
    bool next ( Step & );
    bool nextRandom ( Step& );
    void randomize();
    void reset()
    {
        _stepID = 0;
    }
};
#endif
