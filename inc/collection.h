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

    bool getStep ( uchr, Step& ) const;
    bool getStep ( uchr ID, uchr dir, Step& S ) const;
    bool getStep ( const Stone* st, uchr r2, uchr c3, Step& S ) const;
};
#endif
