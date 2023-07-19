# CSCE 2303 Project 2
## Files
### [InitializeCache](Functions/initializeCache.h)
This function will accest the number of ways and line size as parameters and will use this data to calculate the number of sets and will initalize all the lines in the cache to have a valid bit of 0 to show that the line does not have any meaningful data yet

### [getAddress](Functions/getAddress.h)
This function accepts the memory sddress and uses the line size and number of ways to perform a few calculations on the adress in order to extract from it the offset, the index and the tag. These calculations include:
```
offset bits = log<sub>2</sub>(lineSize)
index bits = log<sub>2</sub>(cache size / (lineSize * numWays)
Tag bits = Address bits - offset bits - index bits
```
### [simCache](Functions/simCache.h)
This function will accept the struct that contains the parts of the memory address, as well as the cache itself and will loop over all the lines in the set checking if the tag of the address matches the line in the cache. Inside this loop, it will check if the valid bit is 0 and will add the adress into the cache, otherise it will continue to check the tag of every line in the set. If the function exists the for loop then no tag was matched and, using a FIFO replacemnt policy the address will replace another in the cache. 

### [utilities](Functions/utilities.h)
Containg all the structs and classes used throughout the other files. These include 
- cacheResType
- CacheLine
- MemAddr

### [main](Functions/main.cpp)
This is the overhead file that brings all the functions together. it includes all 6 given memory generators as well as 2 test ones that we created, 6 functions that simulate the cahe for each given memory generator as well as the two test cases. These functions will first call the initialize function before entering a loop for the given number of iterations, where it will then call the getAddress funxtion and pass that result to the simCache function, of the result is hit, a double variable called hit is incremented. at the end of the for loop, the function will divide the number of hits by the iterations and display the hit ratio on the console. This is done for both test cases and both of the required experiments.

## Contributers
- @useframi1
- @NadSafwat
- @nkasaby
- @Mariam-ElG
