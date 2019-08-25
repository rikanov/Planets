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
    makeStep ( D + ( P - 1 ) * 8 );
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
    static int depth = 0;
    Result ret ( 1 ), src ( -1 );
    Generator possibleSteps ( getCurrentCollection() );
    Step nextStep;
    while ( possibleSteps.next ( nextStep ) )
    {
        if ( isWinnerStep ( nextStep ) )
        {
            return Result ( 1 ); // instant death
        }
        nextStep.step();
        ++depth;
        swapPlayers();
        Result next = depth <= _currentLevel ? test ( src ) : test0();
        swapPlayers();
        --depth;
        nextStep.back();
        if ( next.worseThan ( search_bound ) || next == search_bound )
        {
            return Result(1); // dead branch
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

    result = 1;
    Generator possibleSteps ( getCurrentCollection() );
    possibleSteps.randomize();
    Step nextStep;

    for ( _currentLevel =  1; _currentLevel <= _boundLevel; _currentLevel += 1 )
    {
        Result next ( 1 ), src ( -1 );
        possibleSteps.reset();
        result = possibleSteps.nextRandom ( nextStep );
        result.setStep ( nextStep );

        while ( possibleSteps.nextRandom ( nextStep ) )
        {
            nextStep.step();
            swapPlayers();
            next = test ( src );
            if ( next >> result )
            {
                result.setStep ( nextStep );
            }
            swapPlayers();
            nextStep.back();
        }

        if ( !result.unsure() )
        {
            log("broken")
            break;
        }
    }
    result.swap();
    log3_ ( result.getStep().whatIs(), result, isPlayerTurn() );
    return result;
}
