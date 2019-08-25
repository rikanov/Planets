#include "engine.h"

Engine::Engine()
    :Board ( 5 )
{
    _boundLevel = 5;
    reset();
}

void Engine::makeStep ( uchr token )
{
    Step st;
    getStep ( token, st );
    storeStep ( st );
}

void Engine::makeStep ( uchr P, uchr D )
{
    Step st;
    getStep ( P, D, st );
    storeStep ( st );
}

Result Engine::seeker ( Step& S, Result& search_bound )
{
    static int depth = 0;
    S.step();
    swapPlayers();
    ++depth;
    Result ret = depth <= _currentLevel ? test ( search_bound ) : test0();
    --depth;
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
    Result result = test0();
    if ( result.won() )
    {
        return result;
    }
    Generator possibleSteps ( getCurrentCollection() );
    possibleSteps.randomize();
    Step nextStep;

    for ( _currentLevel =  1; _currentLevel <= _boundLevel; _currentLevel += 1 )
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
            log2_ ( "\nbroken at level:", _currentLevel )
            break;
        }
    }
    result.swap();
    log3_ ( result.getStep().whatIs(), result, stepCount() );
    return result;
}
