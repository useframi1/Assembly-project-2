#ifndef __SIMCACHE_H__
#define __SIMCACHE_H__

#include <iostream>
#include <vector>
#include "utilities.h"
using namespace std;

cacheResType simCache(MemAddr addr, vector<vector<CacheLine>> &cache, vector<int> &replaceCount);

//{{s0,s1,s2,...},{s0,s1,s3,...}} 2-way set associative would look like this
cacheResType simCache(MemAddr addr, vector<vector<CacheLine>> &cache, vector<int> &replaceCount)
{
    int numWays = cache.size();
    // cout << addr.Index << " " << addr.Tag << endl;
    for (int i = 0; i < numWays; i++)
    {
        // cout << i << ": " << cache[i][addr.Index].Tag << " " << cache[i][addr.Index].valid << endl;
        if (!(cache[i][addr.Index].valid))
        {
            // Coldstart MISS
            cache[i][addr.Index].Tag = addr.Tag;
            cache[i][addr.Index].valid = true;
            // cout << i << ": " << cache[i][addr.Index].Tag << " " << cache[i][addr.Index].valid << endl;
            // cout << "COLDSTART MISS" << endl;
            return MISS;
        }
        if (cache[i][addr.Index].Tag == addr.Tag)
        {
            // cout << "HIT" << endl;
            return HIT;
        }
    }

    // Capacity MISS
    cache[replaceCount[addr.Index]][addr.Index].Tag = addr.Tag;
    replaceCount[addr.Index] = ++replaceCount[addr.Index] % numWays;
    // cout << "CAPACITY MISS" << endl;
    return MISS;
}
#endif // __SIMCACHE_H__