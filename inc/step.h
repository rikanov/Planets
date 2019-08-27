#ifndef STEP_HEADER__H
#define STEP_HEADER__H

#include "global.h"
#include "str_node.h"

class Step
{
    const Stone * _pStone;
    const Node * _from;
    const Node * _to;
    uint8_t _token = 0xFF;
public:
    Step();
    Step ( const Stone * S,const Node * to );
    void step() const;
    void back() const;
    void set ( const Stone* S,const Node * N );
    bool isValid() const
    {
        return _to != nullptr;
    }
    const Node * aim() const
    {
        return _to;
    }
    bool inverseOf ( const Step& S ) const
    {
        return _from == S._to && _to == S._from;
    }
    bool inverseOf ( const Step * S ) const
    {
        return _from == S->_to && _to == S->_from;
    }
    void setToken ( uint8_t T )
    {
        _token = T;
    }
    uint8_t getToken() const
    {
        return _token;
    }
    std::string whatIs() const;
};


#endif
