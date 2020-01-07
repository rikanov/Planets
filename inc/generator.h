#ifndef GENERATOR_HEADER__H
#define GENERATOR_HEADER__H

#include "collection.h"

class Generator
{
    const Collection * _coll;
    uint8_t * __permute;
    uint8_t _stepID;

public:
#ifdef CONTINUE_BUILD_CACHE
    static uint8_t * _preSetting;
#endif
    Generator ( const Collection * C,const bool& shuffle = false );
    ~Generator();
    bool next ( Step & );
    bool nextRandom ( Step& );
    void randomize( );
    void reset()
    {
#ifndef CONTINUE_BUILD_CACHE
        _stepID = 0;
#else
        _stepID = *_preSetting != 0xFF ? * ( _preSetting++ ) : 0;
#endif
    }
};
#endif
