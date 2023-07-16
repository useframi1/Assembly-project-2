#ifndef __INITIALIZECACHE_H__
#define __INITIALIZECACHE_H__

#include <iostream>
#include <vector>
#include "utilities.h"
using namespace std;

vector<vector<CacheLine>> initializeCache(int numWays, int lineSize, int &numSets)
{
  vector<vector<CacheLine>> Cache(numWays, vector<CacheLine>());
  numSets = (16 * 1024) / (lineSize * numWays);
  for (int i = 0; i < numWays; i++)
  {
    for (int j = 0; j < numSets; j++)
    {
      CacheLine item;
      item.Tag = 0;
      item.valid = 0;
      Cache[i].push_back(item);
    }
  }

  return Cache;
}

/*int main()
{
  vector<vector<CacheLine>> test = initializeCache(4, 32);
  for (int i = 0; i < test.size(); i++)
  {
    cout << "-------------" << endl;
    for (int j = 0; j < test[i].size(); j++)
    {

      cout << "Row: " << i << " Column: " << j << endl;
      cout << "Tag: " << test[i][j].Tag << " Valid: " << test[i][j].valid << endl;
    }

    cout << "-------------" << endl;
  }
}*/

#endif // __INITIALIZECACHE_H__