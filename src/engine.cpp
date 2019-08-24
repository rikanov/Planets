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
    while ( possibleSteps.next ( nextStep ) ) {
        if ( isWinnerStep ( nextStep ) ) {
            return Result ( 1 );
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
    while ( possibleSteps.next ( nextStep ) ) {
        if ( isWinnerStep ( nextStep ) ) {
            return Result ( 1 ); // instant death
        }
        nextStep.step();
        ++depth;
        swapPlayers();
        Result next = depth <= _currentLevel ? test ( src ) : test0();
        --depth;
        swapPlayers();
        nextStep.back();
        if ( next.worseThan ( search_bound ) || next == search_bound ) {
            ret = next;
            break;
        }
        next >> ret;
    }
    search_bound << ret;
    return ret.swap();
}

Result Engine::getResult()
{
    Result result;
    Generator possibleSteps ( getCurrentCollection() );
    possibleSteps.randomize();
    Step nextStep;

    for ( _currentLevel = 1; _currentLevel <= _boundLevel; _currentLevel += 2 ) {
        Result next ( 1 ), src ( -1 );
        while ( possibleSteps.nextRandom ( nextStep ) ) {
            if ( isWinnerStep ( nextStep ) ) {
                result = 1;
                result.setStep ( nextStep );
                return result;
            }
            nextStep.step();
            swapPlayers();
            if ( test ( src ) >> next ) {
                next.setStep ( nextStep );
            }
            swapPlayers();
            nextStep.back();
        }
        result = next;
        result.setStep ( next.getStep() );
        if ( next < 0 ) {
            break;
        }
        possibleSteps.reset();
    }
    log2_ ( "result:",result.getStep().whatIs() );
    return result;
}
