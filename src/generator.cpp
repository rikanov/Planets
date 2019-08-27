#include "generator.h"

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

void Generator::randomize()
{
    if ( __permute == nullptr )
    {
        __permute = new uchr[40];
        for ( int id = 0; id < 40; ++id )
        {
            __permute[id] = id;
        };
    }
    srand ( time ( NULL ) );
    for ( int shuffles = 5; shuffles; )
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
