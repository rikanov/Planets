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
#include "sstack.h"


static const char* DAT[] = {  "meta_un_2_7.dat", "meta_win_2_7.dat", "meta_lose_2_7.dat" };
  
StepStack::StepStack ( const int& size )
    :_stackSize ( size )
    ,__moveHistory ( nullptr )
{
}

void StepStack::resetStack()
{
    // --- set step stacks for UI -- //
    delete[] __moveHistory; // purify it
    __moveHistory = new Step[_stackSize + 1];
    _currentMove = _lastMove = __moveHistory + 1;
    // -------------- //
}

void StepStack::saveStack(int fileID, int iData )
{
 std::ofstream outfile;
 outfile.open(DAT [fileID], std::ios::app );
  if (iData == 0) log("Unsure")
  if (iData  < 0) log("  Lost")
  if (iData  > 0) log("   win")
  for (auto p = __moveHistory + 2; p != _currentMove + 1; ++p) 
  {
    const int q = (int)p->getToken();
    if (q < 0x10)
    {
      outfile << 0;
      std::cout << 0;
    }
    outfile << std::hex << (int)p->getToken() << ' ';
    std::cout << std::hex << (int)p->getToken() << ' ';
  }
  outfile << '\n';
  log_("")
  outfile.close();
}

void StepStack::storeStep ( Step S )
{
    S.step();
    * ( ++_currentMove ) = S;
    _lastMove = _currentMove;
}

void StepStack::undoStep()
{
    if ( isStarted() )
    {
        ( _currentMove-- )->back();
    }
}

void StepStack::redoStep()
{
    if ( ( _currentMove != _lastMove ) )
    {
        ( ++_currentMove )->step();
    }
}

bool StepStack::isLoop() const
{
    return isStarted() && _currentMove->inverseOf ( _currentMove - 2 );
}

bool StepStack::fromChache(Result& R) const
{
    return _cache.getResult(__moveHistory + 2, _currentMove + 1, R);
}

StepStack::~StepStack()
{
  _outfile[0].close();
  _outfile[1].close();
  _outfile[2].close();
  delete[] __moveHistory;
}
