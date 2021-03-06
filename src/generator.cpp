#include "generator.h"

#ifdef CONTINUE_BUILD_CACHE
uint8_t * Generator::_preSetting = new uint8_t ( 0xFF );
#endif

Generator::Generator ( const Collection * C,const bool& shuffle )
    : _coll ( C )
    , _stepID ( 0 )
    , __permute ( nullptr )
{
    if ( shuffle )
    {
        randomize();
    }
}

bool Generator::next ( Step& S )
{
    if ( _stepID < 40 )
    {
        return _coll->getStep ( _stepID++,S ) ? true : next ( S );
    }
    else
    {
        return false;
    }
}
bool Generator::nextRandom ( Step& S )
{
    if ( _stepID < 40 )
    {
        S.setToken ( __permute[_stepID] );
        return _coll->getStep ( __permute[_stepID++],S ) ? true : nextRandom ( S );
    }
    else
    {
        return false;
    }
}

void Generator::randomize( )
{
    if ( __permute == nullptr )
    {
        __permute = new uint8_t[40];
        for ( uint8_t id = 0; id < 40; ++id )
        {
            __permute[id] = id;
        };
    }
    srand ( time ( NULL ) );
    for ( uint8_t shuffles = 5; shuffles; )
    {
        const int i1 = rand() % 40;
        const int i2 = rand() % 40;
        if ( i1 != i2 )
        {
            std::swap ( __permute[i1], __permute[i2] );
        }
        else
        {
            --shuffles;
        }
    }
}

Generator::~Generator()
{
    delete __permute;
}
