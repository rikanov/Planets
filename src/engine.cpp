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
    ++_deepSearchLevel;
    int reward = _deepSearchLevel - _boundLevel -1; // the worst option: we had already lost
    if ( _deepSearchLevel == _currentMaxLevel ) // it's too deep now. Abort searching
    {
        reward = 0; // unevaluated branch
    }
    else // check the branch of steps, we have chances
    {
        swapPlayers();
        Generator possibleSteps ( getCurrentCollection() );
        Step nextStep;
        const int savedCurrentMaxLevel = _currentMaxLevel;
        while ( possibleSteps.next ( nextStep ) && reward < no_more )
        {
            if ( isWinnerStep ( nextStep ) )
            {
                reward = 1 + _boundLevel - _deepSearchLevel;
                break;
            }
            storeStep ( nextStep );
            if ( checkMaxReward ( reward, yourTurn ( reward ) ) && reward > 0 )
            {
                _currentMaxLevel = _boundLevel - reward;
                /*  clog2('M',_currentMaxLevel)*/
            }
            undoStep();
        }
        _currentMaxLevel = savedCurrentMaxLevel;
        swapPlayers();
    }
    --_deepSearchLevel;
    return reward;
}

int Engine::yourTurn ( const int& no_less )
{
    ++_deepSearchLevel;
    int reward = 1 + _boundLevel - _deepSearchLevel; // the worst option: we had already lost
    if ( _deepSearchLevel == _currentMaxLevel ) // it's too deep now. Abort searching
    {
        reward = 0; // unevaluated branch
    }
    else // check the branch of steps, we have chances
    {
        swapPlayers();
        Generator possibleSteps ( getCurrentCollection() );
        Step nextStep;
        const int savedCurrentMaxLevel = _currentMaxLevel;
        while ( possibleSteps.next ( nextStep ) && reward > no_less )
        {
            if ( isWinnerStep ( nextStep ) )
            {
                reward = _deepSearchLevel - _boundLevel -1;
                break;
            }
            storeStep ( nextStep );
            if ( checkMinReward ( reward, myTurn ( reward ) ) && reward < 0 )
            {
                _currentMaxLevel = _boundLevel + reward;
                /* clog2('Y',_currentMaxLevel)*/
            }
            undoStep();
        }
        _currentMaxLevel = savedCurrentMaxLevel;
        swapPlayers();
    }
    --_deepSearchLevel;
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
        clog ( rewardOfTheNextStep )
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

