#ifndef CACHE_HEADER__H
#define CACHE_HEADER__H
#include "global.h"

class Cache
{
    const uint8_t _opening[14];
    const uint8_t _response[13][8];
public:
    Cache();
    uint8_t getOpeningToken() const;
    uint8_t getResponseToken ( uint8_t token ) const;
};
#endif


