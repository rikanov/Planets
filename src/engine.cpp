#include "engine.h"
#include <thread>

static inline bool checkMaxReward ( int& reward, const int& toCheck )
{
    if ( reward < toCheck )
    {
        reward = toCheck;
        return true;
    }
    return false;
}

static inline bool checkMinReward ( int& reward, const int& toCheck )
{
    if ( reward > toCheck )
    {
        reward = toCheck;
        return true;
    }
    return false;
}

Engine::Engine()
    :Board ( 5 )
{
    _boundLevel = 8;
    _deepSearchLevel = 0;
    reset();
}

int Engine::myTurn ( const int& no_more )
{
    // check node
    if ( isWinnerStep ( ) )
    {
        return 1 + _boundLevel - _deepSearchLevel;
    }
    if ( _deepSearchLevel >= _currentMaxLevel ) // it's too deep now. Abort searching
    {
        return 0; // unevaluated branch
    }
    // check branch
    int reward = _deepSearchLevel - _boundLevel -1; // the worst option: we had already lost
    Generator possibleSteps ( getCurrentCollection() );
    Step nextStep;
    const int savedCurrentMaxLevel = _currentMaxLevel;
    while ( possibleSteps.next ( nextStep ) && reward < no_more )
    {
        storeStep ( nextStep );
        swapPlayers();
        ++_deepSearchLevel;
        if ( checkMaxReward ( reward, yourTurn ( reward ) ) && reward > 0 )
        {
            _currentMaxLevel = _boundLevel - reward;
        }
        --_deepSearchLevel;
        swapPlayers();
        undoStep();
    }
    _currentMaxLevel = savedCurrentMaxLevel;
    return reward;
}

int Engine::yourTurn ( const int& no_less )
{
    // check node
    if ( isWinnerStep ( ) )
    {
        return _deepSearchLevel - _boundLevel -1;
    }
    if ( _deepSearchLevel >= _currentMaxLevel ) // it's too deep now. Abort searching
    {
        return 0; // unevaluated branch
    }
    // check branch
    int reward = 1 + _boundLevel - _deepSearchLevel; // the worst option: we had already lost
    Generator possibleSteps ( getCurrentCollection() );
    Step nextStep;
    const int savedCurrentMaxLevel = _currentMaxLevel;
    while ( possibleSteps.next ( nextStep ) && reward > no_less )
    {
        storeStep ( nextStep );
        swapPlayers();
        ++_deepSearchLevel;
        if ( checkMinReward ( reward, myTurn ( reward ) ) && reward < 0 )
        {
            _currentMaxLevel = _boundLevel + reward;
        }
        --_deepSearchLevel;
        swapPlayers();
        undoStep();
    }
    _currentMaxLevel = savedCurrentMaxLevel;
    return reward;
}

Step Engine::getBestStep()
{
    _currentMaxLevel = _boundLevel;
    int reward = - _currentMaxLevel -2; // it will be better
    Step result, nextStep;
    Generator possibleSteps ( getCurrentCollection() );
    possibleSteps.randomize();
    while ( possibleSteps.nextRandom ( nextStep ) )
    {
        if ( isWinnerStep ( nextStep ) )
        {
            result = nextStep;
            break;
        }
        storeStep ( nextStep );
        const int rewardOfTheNextStep = yourTurn ( reward );
        undoStep();
        clog3(nextStep.whatIs(), ':', rewardOfTheNextStep )
        if ( rewardOfTheNextStep > reward )
        {
            reward = rewardOfTheNextStep;
            result = nextStep;
            if ( reward > 0 )
            {
                _currentMaxLevel = _boundLevel - reward ;
                clog3 ( ">>",_currentMaxLevel,"<<" )
            }
        }
    }
    return result;
}

