#include "engine.h"

Engine::Engine()
    :Board ( 5 )
{
    _boundLevel = 5;
    _deepSearchLevel = 0;
    reset();
}

Result Engine::seeker ( Step& S, Result& search_bound )
{
    S.step();
    swapPlayers();
    ++_deepSearchLevel;
    Result ret = _deepSearchLevel <= _currentLevel ? test ( search_bound ) : test0();
    --_deepSearchLevel;
    swapPlayers();
    S.back();
    return ret;
}

Result Engine::test0()
{
    Generator possibleSteps ( getCurrentCollection() );
    Step nextStep;
    while ( possibleSteps.next ( nextStep ) )
    {
        if ( isWinnerStep ( nextStep ) )
        {
            return Result ( 1 );
        }
    }
    return Result ( 0 );
}

Result Engine::test0_()
{
    Generator possibleSteps ( getCurrentCollection() );
    Step nextStep;
    while ( possibleSteps.next ( nextStep ) )
    {
        if ( isWinnerStep ( nextStep ) )
        {
            Result result ( 1 );
            result.setStep ( nextStep );
            return result;
        }
    }
    return Result ( 0 );
}

Result Engine::test ( Result& search_bound )
{
    Result ret ( 1 ), src ( -1 );
    Generator possibleSteps ( getCurrentCollection() );
    Step nextStep;
    while ( possibleSteps.next ( nextStep ) )
    {
        if ( isWinnerStep ( nextStep ) )
        {
            return Result ( 1 ); // instant death
        }
        Result next = seeker ( nextStep, src );
        if ( next.worseThan ( search_bound ) || next == search_bound )
        {
            return Result ( 1 ); // dead branch
        }
        next >> ret;
    }
    search_bound << ret;
    return ret.swap();
}

Result Engine::getResult()
{
    Result result;
    Step nextStep;
    if ( _boundLevel > 6 && !isStarted() )
    {
        getStep ( _cache.getOpeningToken(), nextStep );
        result.setStep ( nextStep );
        return result;
    }
    if ( _boundLevel > 6 && stepCount() == 1 )
    {
        getStep ( _cache.getResponseToken ( moveHistory ( -1 ).getToken() ), nextStep );
        result.setStep ( nextStep );
        return result;
    }
    result = test0_();
    if ( result.won() )
    {
        return result;
    }
    Generator possibleSteps ( getCurrentCollection() );
    possibleSteps.randomize();
    const int bound = ( stepCount() < 5 && _boundLevel < 7 ) ? 7 :  _boundLevel;
    for ( _currentLevel =  1; _currentLevel <= bound; _currentLevel += 1 )
    {
        Result next ( 1 ), src ( -1 );
        possibleSteps.reset();
        possibleSteps.nextRandom ( nextStep );
        result = seeker ( nextStep, src );
        result.setStep ( nextStep );
        while ( possibleSteps.nextRandom ( nextStep ) )
        {
            next = seeker ( nextStep, src );
            if ( next >> result )
            {
                result.setStep ( nextStep );
            }
        }

        if ( !result.unsure() )
        {
            break;
        }
    }
    result.swap();
    return result;
}
