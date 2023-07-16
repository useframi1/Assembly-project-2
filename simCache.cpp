#ifndef __SIMCACHE_H__
#define __SIMCACHE_H__

#include <iostream>
#include <vector>
using namespace std;

enum cacheResType
{
    MISS = 0,
    HIT = 1
};

struct CacheLine
{
    bool valid;
    int Tag;
};

struct MemAddr
{
    int Tag;
    int Index;
    int Offset;
};

cacheResType simCache(MemAddr addr, vector<vector<CacheLine>> &cache, vector<int> &replaceCount);

//{{s0,s1,s2,...},{s0,s1,s3,...}} 2-way set associative would look like this
cacheResType simCache(MemAddr addr, vector<vector<CacheLine>> &cache, vector<int> &replaceCount)
{
    int numWays = cache.size();
    for (int i = 0; i < numWays; i++)
    {
        if (!(cache[i][addr.Index].valid))
        {
            // Coldstart MISS
            cache[i][addr.Index].Tag == addr.Tag;
            cache[i][addr.Index].valid == true;
            return MISS;
        }
        if (cache[i][addr.Index].Tag == addr.Tag)
            return HIT;
    }

    // Capacity MISS
    cache[replaceCount[addr.Index]][addr.Index].Tag = addr.Tag;
    replaceCount[addr.Index] = ++replaceCount[addr.Index] % numWays;
    return MISS;
}
#endif // __SIMCACHE_H__