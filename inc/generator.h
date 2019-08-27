#ifndef GENERATOR_HEADER__H
#define GENERATOR_HEADER__H

#include "collection.h"

class Generator
{
    const Collection * _coll;
    uint8_t * __permute;
    uint8_t _stepID;

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
