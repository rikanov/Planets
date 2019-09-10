#ifndef DATACACHE_H
#define DATACACHE_H

#include "global.h"
#include "result.h"

class DataLine
{
    Result _result;
    DataLine ** _route;
    
public:
    DataLine();
    ~DataLine();
    
    DataLine* route(uint8_t);
    void storeRoute(const std::string& way, Result R);
    void setResult(Result R) { _result = R; }
    Result getResult() const { return _result; }
    
};
class DataCache
{
    int _counter = 0;
    DataLine * _root;
public:
    /**
     * Default constructor
     */
    DataCache();
    void readFromFile(const std::string& prefix, const std::string& suffix );
    bool getResult(const Step* , const Step*, Result&) const;
    int count() const { return _counter; }
    /**
     * Destructor
     */
    ~DataCache();

};

#endif // DATACACHE_H
