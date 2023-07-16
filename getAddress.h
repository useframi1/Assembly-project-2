#ifndef __GETADDRESS_H__
#define __GETADDRESS_H__

#include <iostream>
#include "utilities.h"
using namespace std;

#define Cache_Size (16 * 1024) // Fixed Cache size 16 KBytes

void getAddress(MemAddr &address, int numWays, int lineSize, int addr)
{
     /*
          Bit Division:

          offset bits= log(lineSize)
          index bits = log(cache size/ (lineSize* numWays))
          tag bits are the remaining bits

     */
     address.Offset = addr % lineSize;
     address.Index = (addr / lineSize) % (Cache_Size / (lineSize * numWays));
     address.Tag = (addr / lineSize) / (Cache_Size / (lineSize * numWays));
}

/*int main()
{
     // Test:
     MemAddr test1;
     getAddress(test1, 4, 16, 43456789);
     cout << "Offset: " << test1.Offset << endl;
     cout << "Index: " << test1.Index << endl;
     cout << "Tag: " << test1.Tag << endl;
}
*/
#endif // __GETADDRESS_H__