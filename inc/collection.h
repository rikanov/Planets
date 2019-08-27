#ifndef COLLECTION_HEADER__H
#define COLLECTION_HEADER__H

#include "stone.h"

enum Turn
{
    MINE,
    YOURS
};

class Collection
{
    Stone ** __collection;

public:
    Collection ( Turn, const Node * );
    ~Collection();

    bool getStep ( uint8_t, Step& ) const;
    bool getStep ( uint8_t ID, uint8_t dir, Step& S ) const;
    bool getStep ( const Stone* st, uint8_t r2, uint8_t c3, Step& S ) const;
};
#endif
