#include <iostream>
#include "getAddress.h"
#include "initializeCache.h"
#include "simCache.h"
#include "utilities.h"

using namespace std;

#define DRAM_SIZE (64 * 1024 * 1024)

/* The following implements a random number generator */
unsigned int m_w = 0xABABAB55; /* must not be zero, nor 0x464fffff */
unsigned int m_z = 0x05080902; /* must not be zero, nor 0x9068ffff */
unsigned int rand_()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w; /* 32-bit result */
}

unsigned int memGen1()
{
    static unsigned int addr = 0;
    return (addr++) % (DRAM_SIZE);
}

unsigned int memGen2()
{
    static unsigned int addr = 0;
    return rand_() % (24 * 1024);
}

unsigned int memGen3()
{
    return rand_() % (DRAM_SIZE);
}

unsigned int memGen4()
{
    static unsigned int addr = 0;
    return (addr++) % (4 * 1024);
}

unsigned int memGen5()
{
    static unsigned int addr = 0;
    return (addr++) % (1024 * 64);
}

unsigned int memGen6()
{
    static unsigned int addr = 0;
    return (addr += 32) % (64 * 4 * 1024);
}

void runSim1(int numWays, int lineSize, double iterations)
{
    double hit = 0;
    int numSets;
    vector<vector<CacheLine>> cache = initializeCache(numWays, lineSize, numSets);
    vector<int> replaceIndex(numSets, 0);
    cacheResType r;
    MemAddr addr;
    for (int i = 0; i < iterations; i++)
    {
        int x = memGen1();
        getAddress(addr, numWays, lineSize, x);
        r = simCache(addr, cache, replaceIndex);
        if (r == HIT)
            hit++;
    }
    cout << "\t Hit ratio = " << (hit / iterations) << endl;
}

void runSim2(int numWays, int lineSize, double iterations)
{
    double hit = 0;
    int numSets;
    vector<vector<CacheLine>> cache = initializeCache(numWays, lineSize, numSets);
    vector<int> replaceIndex(numSets, 0);
    cacheResType r;
    MemAddr addr;
    for (int i = 0; i < iterations; i++)
    {
        int x = memGen2();
        getAddress(addr, numWays, lineSize, x);
        r = simCache(addr, cache, replaceIndex);
        if (r == HIT)
            hit++;
    }
    cout << "\t Hit ratio = " << (hit / iterations) << endl;
}

void runSim3(int numWays, int lineSize, double iterations)
{
    double hit = 0;
    int numSets;
    vector<vector<CacheLine>> cache = initializeCache(numWays, lineSize, numSets);
    vector<int> replaceIndex(numSets, 0);
    cacheResType r;
    MemAddr addr;
    for (int i = 0; i < iterations; i++)
    {
        int x = memGen3();
        getAddress(addr, numWays, lineSize, x);
        r = simCache(addr, cache, replaceIndex);
        if (r == HIT)
            hit++;
    }
    cout << "\t Hit ratio = " << (hit / iterations) << endl;
}

void runSim4(int numWays, int lineSize, double iterations)
{
    double hit = 0;
    int numSets;
    vector<vector<CacheLine>> cache = initializeCache(numWays, lineSize, numSets);
    vector<int> replaceIndex(numSets, 0);
    cacheResType r;
    MemAddr addr;
    for (int i = 0; i < iterations; i++)
    {
        int x = memGen4();
        getAddress(addr, numWays, lineSize, x);
        r = simCache(addr, cache, replaceIndex);
        if (r == HIT)
            hit++;
    }
    cout << "\t Hit ratio = " << (hit / iterations) << endl;
}

void runSim5(int numWays, int lineSize, double iterations)
{
    double hit = 0;
    int numSets;
    vector<vector<CacheLine>> cache = initializeCache(numWays, lineSize, numSets);
    vector<int> replaceIndex(numSets, 0);
    cacheResType r;
    MemAddr addr;
    for (int i = 0; i < iterations; i++)
    {
        int x = memGen5();
        getAddress(addr, numWays, lineSize, x);
        r = simCache(addr, cache, replaceIndex);
        if (r == HIT)
            hit++;
    }
    cout << "\t Hit ratio = " << (hit / iterations) << endl;
}

void runSim6(int numWays, int lineSize, double iterations)
{
    double hit = 0;
    int numSets;
    vector<vector<CacheLine>> cache = initializeCache(numWays, lineSize, numSets);
    vector<int> replaceIndex(numSets, 0);
    cacheResType r;
    MemAddr addr;
    for (int i = 0; i < iterations; i++)
    {
        int x = memGen6();
        getAddress(addr, numWays, lineSize, x);
        r = simCache(addr, cache, replaceIndex);
        if (r == HIT)
            hit++;
    }
    cout << "\t Hit ratio = " << (hit / iterations) << endl;
}

int main()
{
    int numWays[5] = {1, 2, 4, 8, 16};
    int lineSize[4] = {16, 32, 64, 128};
    double iterations = 1000000;

    cout << "Experiment 1: " << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << "Line Size: " << lineSize[i] << endl;
        cout << "\t MemGen1:";
        runSim1(numWays[2], lineSize[i], iterations);
        cout << "\t MemGen2:";
        runSim2(numWays[2], lineSize[i], iterations);
        cout << "\t MemGen3:";
        runSim3(numWays[2], lineSize[i], iterations);
        cout << "\t MemGen4:";
        runSim4(numWays[2], lineSize[i], iterations);
        cout << "\t MemGen5:";
        runSim5(numWays[2], lineSize[i], iterations);
        cout << "\t MemGen6:";
        runSim6(numWays[2], lineSize[i], iterations);
    }

    cout << endl
         << "Experiment 2: " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "Number of Ways: " << numWays[i] << endl;
        cout << "\t MemGen1:";
        runSim1(numWays[i], lineSize[1], iterations);
        cout << "\t MemGen2:";
        runSim2(numWays[i], lineSize[1], iterations);
        cout << "\t MemGen3:";
        runSim3(numWays[i], lineSize[1], iterations);
        cout << "\t MemGen4:";
        runSim4(numWays[i], lineSize[1], iterations);
        cout << "\t MemGen5:";
        runSim5(numWays[i], lineSize[1], iterations);
        cout << "\t MemGen6:";
        runSim6(numWays[i], lineSize[1], iterations);
    }
    return 0;
}