#ifndef SGEN_INTERFACE_HEADER__H
#define SGEN_INTERFACE_HEADER__H

template <class T>
class iSgen
{
public:
    virtual const T* start() = 0;
    virtual const T* next() = 0;

};
#endif

