#ifndef COLLECTION_HEADER__H
#define COLLECTION_HEADER__H

#include "stone.h"

enum Opponent
{
    MINE,
    YOURS
};

class Collection
{
    Stone ** __collection;
    const uint8_t _size;

public:
    Collection ( Opponent, const Node *, uint8_t );
    ~Collection();

    bool getStep ( uint8_t, Step& ) const;
    bool getStep ( uint8_t ID, uint8_t dir, Step& S ) const;
    bool getStep ( const Stone* st, uint8_t r2, uint8_t c3, Step& S ) const;
    void getPos ( uint8_t, uint8_t&, uint8_t& ) const;
};
#endif
