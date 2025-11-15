/*
   ========================================
   hash_fn.cpp — implement your hash functions
   ========================================

   Description:
    This file contains the hash functions for integer and string keys.

   Development History:
    - 2025/11/11: Initial implementation

   Developer: Yu-Feng Huang <yfhuang@saturn.yzu.edu.tw>
 */

//g++ main.cpp -o hash_test
//./hash_test
#include <string>
#include <cstdlib>
#include <cstdint>

int myHashInt(int key, int m) {
    // TODO: replace with your own design
    //return key % m;  // basic division method
    return (key + 11) % m;
}

int myHashString(const std::string& str, int m) {
    unsigned long hash = 0;
    // TODO: replace with your own design
    return static_cast<int>(hash % m);  // basic division method
}
