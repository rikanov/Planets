#ifndef BASICUI_HEADER__H
#define BASICUI_HEADER__H

#include "engine.h"

class BasicUI: public Engine
{
public:
    BasicUI();
    void start();
    void makeStep ( uint8_t );
    void makeStep ( uint8_t, uint8_t );
    void autoplay ( const int&, const int& );
};
#endif
