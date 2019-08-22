#include "stone.h"

Stone * Stone::WALL = new Stone(nullptr,"WALL");

Step::Step()
    :_from(nullptr)
    ,_to(nullptr)
    ,_pStone(nullptr)
{
}

Step::Step(const Stone * S, const Node * N)
    :_from(S->getNode())
    ,_to(N)
    ,_pStone(S)
{
}

void Step::set(const Stone* S, const Node * N)
{
    _pStone = S;
    _from = S->getNode();
    _to = N;
}

void Step::step() const
{
    _pStone->step(_to);
}

void Step::back() const
{
    _pStone->step(_from);
}

void Stone::step(const Node * N) const
{
    _pNode->setStone(nullptr);
    _pNode = N;
    _pNode->setStone(this);
}
