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
#include <cmath>
#include <stdexcept>

int myHashInt(int key, int m) {
    // TODO: replace with your own design
    //return key % m;  // basic division method
    
    if (m <= 0) //檢查 table sizes 不可 <= 0
        throw std::invalid_argument("table size m must be > 0");

    //Multiplication Method
    const double A = 0.618; // 黃金比例倒數
    double frac = (key * A)- floor(key * A); ////只取小數部分不然數值太大
    return int(m * frac);
}

int myHashString(const std::string& str, int m) {
    unsigned long hash = 0;
    // TODO: replace with your own design
    //return static_cast<int>(hash % m);  // basic division method

    if (m <= 0) //檢查 table sizes 不可 <= 0
        throw std::invalid_argument("table size m must be > 0");
    if (str.empty()) //處理空字串
        return 0;

    //Multiplication Method
    const int base = 31;
    double A = 0.168;
    for (char c : str) //把字串轉成數字
        hash = hash * base + c; 
    double frac = hash*A - floor(hash*A); //取小數部分
    return int (m * frac);
}
