#include "cache.h"

Cache::Cache()
    :_opening { 3, 3, 4, 4, 11, 13, 20, 20, 27, 29, 36, 36, 37, 37 }
    ,_response
{
    //  ID size |-- response tokens --|
    {  0,  1, 20,  0,  0,  0,  0,  0}, // (1, 0): 0
    {  1,  1, 28,  0,  0,  0,  0,  0}, // (1, 1): 1
    {  8,  4,  4, 13, 20, 36,  0,  0}, // (2, 0): 8
    {  9,  6,  3, 11, 20, 20, 20, 28}, // (2, 1): 9
    { 15,  4,  3, 20, 29, 37,  0,  0}, // (2, 7): 15
    { 17,  6, 37, 13,  4,  3,  3,  3}, // (3, 1): 17
    { 16,  2,  3, 37,  0,  0,  0,  0}, // (3, 0): 16
    { 23,  6,  3, 27, 36, 37, 37, 37}, // (3, 7): 23
    { 31,  6, 37, 29, 20, 20, 20, 12}, // (4, 7): 31
    { 25,  4, 37, 20, 11,  3,  0,  0}, // (4, 1): 25
    { 24,  4, 36, 27, 20,  4,  0,  0}, // (4, 0): 24
    { 39,  1, 12,  0,  0,  0,  0,  0}, // (5, 7): 39
    { 32,  1, 20,  0,  0,  0,  0,  0}  // (5, 0): 32
}
{
    srand ( time ( NULL ) );
}

uint8_t Cache::getOpeningToken() const
{
    return _opening[rand() % 14];
}

uint8_t Cache::getResponseToken ( uint8_t token ) const
{
    for ( int index = 0; index < 13; ++index )
    {
        if ( _response[index][0] == token )
        {
            return _response[index][2 + /*offset*/ rand() % _response[index][1] /* = size */];
        }
    }
    log2_ ( "unhandled cache exception, token ID:", ( int ) token )
    return 0xFF; // invalid
}
