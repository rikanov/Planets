/*
 * BlackHole -- a simple abstract board game designed by myself
 * Copyright (C) 2019  Robert Ikanov, robert.ikanov@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef STRUCT_NODE_H
#define STRUCT_NODE_H

#include "global.h"

class Stone;
class Node
{
  Node* __next[8] = {};
  mutable const Stone * _pStone = nullptr;
  int _row = 0, _col = 0;
public:
  const Node * go(const uchr&) const;
  void connect( Node* N, const uchr& D) {
    __next[D] = N;
  }
  const Stone * getStone() const {
    return _pStone;
  }
  void setStone(const Stone * S) const {
    _pStone = S;
  }
  void setPos(uchr R, uchr C) {
    _row = R;
    _col = C;
  }
  bool isEmpty() const {
    return _pStone == nullptr;
  }
  const Node * next(uchr U) const {
    return __next[U];
  }
  std::string getName() const;
  bool operator == (const Node& N) const {
    return _row == N._row && _col == N._col;
  }
  bool operator != (const Node& N) const {
    return _row != N._row || _col != N._col;
  }

};

#endif
