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

inline void makeSuffix(std::string& suffix, char s, char d)
{
        suffix = "_";
        suffix.push_back(s);
        suffix.push_back('_');
        suffix.push_back(d);
        suffix.append(".dat");
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
    std::stringstream toRoute(way);
    DataLine * current = this;
    
    for (int r = 0; toRoute >> std::hex >> r; current = current->route(r) );
    
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
            _root->storeRoute(nextLine + "\t", (int)res);
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
