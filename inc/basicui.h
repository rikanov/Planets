#ifndef BASICUI_HEADER__H
#define BASICUI_HEADER__H

#include "engine.h"

class BasicUI: public Engine
{
public:
    BasicUI();
    void start();
    void makeStep ( uchr );
    void makeStep ( uchr, uchr );
    void autoplay ( const int&, const int& );
};
#endif
