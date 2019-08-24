#ifndef COLLECTION_HEADER__H
#define COLLECTION_HEADER__H

#include "stone.h"

enum Turn {
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
};
#endif
