#ifndef __UTILITIES_H__
#define __UTILITIES_H__

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
#endif // __UTILITIES_H__