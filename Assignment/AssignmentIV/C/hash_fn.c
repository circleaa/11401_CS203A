/*
   ========================================
   hash_fn.c — implement your hash functions
   ========================================

   Description:
    This file contains the hash functions for integer and string keys.

   Development History:
    - 2025/11/11: Initial implementation

   Developer: Yu-Jia Wang 王郁佳 <s1121430@mail.yzu.edu.tw> <ariel940814@gmail.com>
 */
#include <stdio.h>

int myHashInt(int key, int m) {
    if (m <= 0) { //檢查 table sizes 不可 <= 0
        fprintf(stderr, "Error: table size m must be > 0.\n");
        return -1;
    }

    return key % m;  // division method example
}

int myHashString(const char* str, int m) {
    unsigned long hash = 0;
    if (m <= 0) { //檢查 table sizes 不可 <= 0
        fprintf(stderr, "Error: table size m must be > 0.\n");
        return -1;
    }
    if (str == NULL) { //錯誤處理無字串
        fprintf(stderr, "Error: string key is NULL.\n");
        return -1;
    }
    if (str[0] == '\0')  //處理空字串，放到index=0
        return 0;

    return (int)(hash % m); // basic division method
}