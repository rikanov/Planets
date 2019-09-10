/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2019  Robert Ikanov <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "datacache.h"

static inline void makeSuffix(std::string& suffix, char s, char d)
{
        suffix = "_";
        suffix.push_back(s);
        suffix.push_back('_');
        suffix.push_back(d);
        suffix.append(".dat");
}

static inline void flipV(int& r)
{
    r = 8 * ( 4 - r / 8 ) /* swapplanets */ + ( 8 - r % 8 ) % 8 /* rotate direction */;
}

static inline void flipH(int& r)
{
    uint8_t d;
    switch( r % 8 )
    {
        case 0:
            d = 4;
            break;
        case 1:
            d = 3;
            break;
        case 2:
            d = 2;
            break;
        case 3:
            d = 1;
            break;
        case 4:
            d = 0;
            break;
        case 5:
            d = 7;
            break;
        case 6:
            d = 6;
            break;
        case 7:
            d = 5;
            break;
        default:
            d = 0;
            log("error")
            break;
    }
    r &= 111000;
    r += d;    
}

DataLine::DataLine()
:_route(new DataLine* [40] { nullptr } ) 
{
}

DataLine::~DataLine()
{
    for(int id = 0 ; id < 40; ++id)
    {
        delete _route[id];
    }
    delete[] _route;
}

DataLine* DataLine::route(uint8_t way)
{
    if(_route[way] == nullptr)
    {
        _route[way] = new DataLine();
    }
    return _route[way];
}

void DataLine::storeRoute(const std::string& way, Result R)
{
    DataLine * current = this;
    
    std::stringstream toRoute(way);
    for (int r = 0; toRoute >> std::hex >> r; current = current->route(r) );
    current->setResult(R);
    
    current = this;
    std::stringstream flipVer(way);
    for (int r = 0; flipVer >> std::hex >> r; current = current->route(r) )
    {
        flipV(r);
    }
    current->setResult(R);
    
    current = this;
    std::stringstream flipHor(way);
    for (int r = 0; flipHor >> std::hex >> r; current = current->route(r) )
    {
        flipH(r);
    }
    current->setResult(R);
    
    current = this;
    std::stringstream flip(way);
    for (int r = 0; flip >> std::hex >> r; current = current->route(r) )
    {
        flipV(r);
        flipH(r);
    }
    current->setResult(R);
}

DataCache::DataCache()
: _root(new DataLine() )
{
    const std::string prefix ("cache/meta_");
    for( char s: { '1', '2', '3'} )
        for( char d: { '0', '1', '7'} )
        {
            if ( s != '2' && d == '7')
            {
                continue;
            }
            std::string suffix;
            makeSuffix(suffix, s, d);
            readFromFile(prefix, suffix);
        }
        log2_("counter:",_counter)
}

void DataCache::readFromFile(const std::string& prefix, const std::string& suffix)
{ 
    for ( auto result: { "lose", "un", "win"})
    {
        int res = 0; 
        const char first = result[0];
        if ( first == 'l' /* lose */)
        {
            res = -8;
        }
        else if ( first == 'w' /* win */)
        {
            res = 7;
        }
        std::string fileName = prefix + result + suffix ;
        log(fileName);
        std::ifstream file(fileName);
        log_(file.is_open())
        int C = 0;
        for (std::string nextLine; std::getline(file, nextLine); )
        {
           ++ _counter; ++C; if (C < 20) {log_("  " + nextLine) }
            _root->storeRoute(nextLine , res);
        }
        file.close();
    }
}

bool DataCache::getResult(const Step* begin, const Step* end, Result& R) const
{
    DataLine * current = _root;
    for (auto p = begin; p != end; ++p)
    {
        if ( current == nullptr)
        {
            return false;
        }
        current = current->route(p->getToken());
    }
    R = current->getResult();
    return R != -1;
}

DataCache::~DataCache()
{
    delete _root;
}
