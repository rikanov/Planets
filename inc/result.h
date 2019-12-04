#ifndef RESULT_HEADER__H
#define RESULT_HEADER__H

#include "step.h"

class Result
{
    int _result;
    Step _step;
    static inline int sgn ( int R )
    {
        return R == 0 ? 0 : ( R < 0 ? -1 : 1 );
    }
public:

    static const Result Best;
    static const Result Worst;
    static const Result Unsure;

    Result ( const int& R = -1 ) : _result ( R ) {}
    const int& result() const
    {
        return _result;
    }
    operator int()
    {
        return _result;
    }
    const int& operator = ( const int& r )
    {
        return ( _result = r );
    }
    bool operator == ( const int& r ) const
    {
        return _result == r;
    }
    bool operator == ( const Result& R ) const
    {
        return _result == R._result;
    }
    bool operator != ( const int& r ) const
    {
        return _result != r;
    }
    bool operator != ( const Result& R ) const
    {
        return _result != R._result;
    }
    bool operator <= ( const int& r ) const
    {
        return _result <= r;
    }
    bool operator < ( const int& r ) const
    {
        return _result < r;
    }
    bool operator >= ( const int& r ) const
    {
        return _result >= r;
    }
    bool operator > ( const int& r ) const
    {
        return _result > r;
    } //*/
    const Result swap() const
    {
        return Result ( -_result - sgn ( _result ) );
    }
    bool worseThan ( const Result& R ) const
    {
        return ( _result <  0 && ( R._result < _result || R._result >= 0 ) )
               || ( _result >  0 && ( R._result < _result && R._result >  0 ) )
               || ( _result == 0 && R._result > _result );
    }
    bool operator << ( const Result& R )
    {
        const bool success = worseThan ( R );
        if ( success )
        {
            _result = R._result;
        }
        return success;
    }
    bool operator >> ( Result& R ) const
    {
        const bool success = worseThan ( R );
        if ( success )
        {
            R._result = _result;
        }
        return success;
    }
    bool lost() const
    {
        return _result < 0;
    }
    bool won() const
    {
        return _result > 0;
    }
    bool unsure() const
    {
        return _result == 0;
    }
    void setStep ( const Step& S )
    {
        _step = S;
    }
    const Step& getStep() const
    {
        return _step;
    }
};

#endif
