#ifndef STONE_HEADER__H
#define STONE_HEADER__H

#include "global.h"
#include "str_node.h"
#include "sgen_interface.h"

class Step
{
    const Stone * _pStone;
    const Node * _from;
    const Node * _to;
public:
    Step();
    Step(const Stone * S,const Node * to);
    void step() const;
    void back() const;
    void set(const Stone* S,const Node * N);
    bool isValid() const {
        return _to != nullptr;
    }
};

class Stone
{
    std::string _name; // for basic ui only
    mutable const Node * _pNode;
public:
    Stone(const Node* N, const std::string& S) : _pNode(N), _name(S) {
        if (_pNode)
            _pNode->setStone(this);
    }
    const Node * go(uchr D) const {
        const Node * ret = _pNode->go(D);
        return ret != _pNode ? ret : nullptr;
    }
    void step(const Node*) const;
    const Node* getNode() const {
        return _pNode;
    }
    std::string getName() const {
        return _name;
    }
    static Stone * WALL;
};

#endif
