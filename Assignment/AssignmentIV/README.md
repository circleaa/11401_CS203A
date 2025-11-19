# Homework Assignment IV: Hash Function Design & Observation (C/C++ Version)

- Developer: Yu-Jia Wang 王郁佳 
- Email: <s1121430@mail.yzu.edu.tw> / <ariel940814@gmail.com> 
 ---
## My Hash Function (C++ Version)
- 我使用較常見的一種方法來做實作: **Multiplication Method**  
Multiplication method 是 Donald Knuth 在 TAOCP 中提出的 Hashing 方法。
它使用「乘法 + 小數部分」來把 key **均勻分佈**到 Hash Table 中。
```text
    標準公式：h(k)=⌊m(kAmod1)⌋
    其中：
        - k = 你的 key（整數）
        - m = hash table 大小
        - A = 一個固定常數（0 < A < 1) 通常選 A = (√5 – 1)/2 = 0.6180339887...
```    
- Multiplication method的好處  
Division method（% m）會很容易被看出規律，較適合去處理連續的 keys  
而 Multiplication method 則是透過「**小數部分**」去**破壞規律、避免週期性**，使處理過後的 key 值像亂數一樣分布
### Integer Keys 
- Formula / pseudocode:
  ```text
    int myHashInt(int key, int m) {
        if (m <= 0) //檢查 table sizes 不可 <= 0
            throw std::invalid_argument("table size m must be > 0");

        //Multiplication Method
        const double A = 0.618; // 黃金比例倒數
        double frac = (key * A)- floor(key * A); //只取小數部分不然數值太大
        return int(m * frac);
    }
  ```
- Rationale: h(k) = floor(m*(k*A mod 1)), 0 < A < 1 (研究顯示A 約 0.618時效果最好)

### Non-integer Keys
- Formula / pseudocode:
  ```text
    int myHashString(const std::string& str, int m) {
        unsigned long hash = 0;
        if (m <= 0) //檢查 table sizes 不可 <= 0
            throw std::invalid_argument("table size m must be > 0");
        if (str.empty()) //處理空字串，放到index=0
            return 0;

        //Multiplication Method
        const int base = 31;
        double A = 0.168;
        for (char c : str) //把字串轉成數字
            hash = hash * base + c; 
        double frac = hash*A - floor(hash*A); //取小數部分
        return int (m * frac);
    }
  ```
- Rationale: h(k) = floor(m*(k*A mod 1)), 0 < A < 1 (研究顯示A 約 0.618時效果最好)

## Experimental Setup
- Table sizes tested (m): 10, 11, 37
- Test dataset:
  - Integers: 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60
  - Strings: "cat", "dog", "bat", "cow", "ant", "owl", "bee", "hen", "pig", "fox"
- Compiler: GCC and G++
- Standard: C23 and C++23

## Results
### Initial - Division Method -> h(k) = k mod m
**Integer Hash**  
| Table Size (m) | Index Sequence | Collision Rate | Observation |
|----------------|----------------|----------------|-------------|
| 10 | 1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 | 10/20=**50%** | **Pattern repeats every 10** |
| 11 | 10,0,1,2,3,4,5,6,7,8,7,8,9,10,0,1,2,3,4,5 | 9/20=**45%** | **More uniform** |
| 37 | 21,22,23,24,25,26,27,28,29,30,14,15,16,17,18,19,20,21,22,23 | 3/20=**15%** | **Near-uniform** |

**String Hash**  
| Table Size (m) | Index Sequence | **Collision Rate** | **Observation** |
|----------------|----------------|----------------|-------------|
| 10 | 0,0,0,0,0,0,0,0,0,0 | 9/10=**90%** | **All zero** |
| 11 | 0,0,0,0,0,0,0,0,0,0 | 9/10=**90%** | **All zero** |
| 37 | 0,0,0,0,0,0,0,0,0,0 | 9/10=**90%** | **All zero** |
 ---
### Multiplication Method -> h(k) = floor(m*(k*A mod 1))
**Integer Hash** 
| Table Size (m) | Index Sequence | **Collision Rate** | **Observation** |
|----------------|----------------|----------------|-------------|
| 10 | 9,5,2,8,4,0,6,3,9,5,5,1,7,3,9,6,2,8,4,0 | 10/20=**50%** | **Pattern repeats every 10** |
| 11 | 10,6,2,9,4,0,7,3,10,5,5,1,8,4,10,6,2,9,5,0 | 9/20=**45%** | **More uniform** |
| 37 | 36,22,7,30,16,2,25,11,34,19,19,5,27,13,36,22,8,31,17,2 | 4/20=**20%** | **Near-uniform** |

**String Hash**  
| Table Size (m) | Index Sequence | **Collision Rate** | **Observation** |
|----------------|----------------|----------------|-------------|
| 10 | 9,9,0,9,1,2,3,3,8,2 | 4/10=**40%** | **Near-uniform** |
| 11 | 10,10,0,10,1,2,4,3,9,3 | 3/10=**30%** | **Near-uniform** |
| 37 | 33,36,0,36,6,8,14,12,30,10 | 1/10=**10%** | **Near-uniform** |

## Compilation, Build, Execution, and Output

### Compilation
- The project uses a comprehensive Makefile that builds both C and C++ versions with proper flags:
  ```bash
  # Build both C and C++ versions
  make all
  
  # Build only C version
  make c
  
  # Build only C++ version
  make cxx
  ```

### Manual Compilation (if needed)
- Command for C:
  ```bash
  gcc -std=c23 -Wall -Wextra -Wpedantic -g -o C/hash_function C/main.c C/hash_fn.c
  ```
- Command for C++:
  ```bash
  g++ -std=c++23 -Wall -Wextra -Wpedantic -g -o CXX/hash_function_cpp CXX/main.cpp CXX/hash_fn.cpp
  ```

### Clean Build Files
- Remove all compiled files:
  ```bash
  make clean
  ```

### Execution
- Run the compiled binary:
  ```bash
  ./hash_function
  ```
  or
  ```bash
  ./hash_function_cpp
  ```

### Result Snapshot
 - C++ Version  
Example output for integers:  
<img src="Images/C++1.png" width="300">  
Example output for strings:  
<img src="Images/C++2.png" width="300">

 - C Version  
Example output for integers:
<img src="Images/C1.png" width="300">  
Example output for strings:  
<img src="Images/C2.png" width="300">

- Observations: Outputs align with the analysis, showing better distribution with prime table sizes.
- Example output for integers:
  ```
  Hash table (m=10): [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
  Hash table (m=11): [10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  Hash table (m=37): [20, 21, 22, 23, 24, 25, 26, 27, 28, 29, ...]
  ```
- Example output for strings:
  ```
  Hash table (m=10): ["cat", "dog", "bat", "cow", "ant", ...]
  Hash table (m=11): ["fox", "cat", "dog", "bat", "cow", ...]
  Hash table (m=37): ["bee", "hen", "pig", "fox", "cat", ...]
  ```
- Observations: Outputs align with the analysis, showing better distribution with prime table sizes.

## Analysis
- Prime vs non-prime `m`: Prime table sizes generally result in better distribution and fewer collisions.
- Patterns or collisions: Non-prime table sizes tend to produce repetitive patterns, leading to more collisions.
- Improvements: Use a prime table size and a well-designed hash function to enhance distribution.

## Reflection
1. Designing hash functions requires balancing simplicity and effectiveness to minimize collisions.
2. Table size significantly impacts the uniformity of the hash distribution, with prime sizes performing better.
3. The design using a prime table size and a linear transformation formula produced the most uniform index sequence.

 ---
 ---

 - Collision Rate (碰撞率) = 同一個 table size 下，不同 key 對應到相同 hash index 的比例
 - Uniformity（分布均勻度）: 每個 index 的 key 分布
 ---
## Initial - Division Method 
 - h(k) = k mod m
### Integer Hash 
| table sizes (m) | Key Indices | **unique indices** | **collisions** | **collision rate** |
|------------------|------------|-----------------|------------|------------|
| **m=10** | 1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 | 10 | 10 | 50% |
| **m=11** | 10,0,1,2,3,4,5,6,7,8,7,8,9,10,0,1,2,3,4,5 | 11 | 9 | 45% |
| **m=37** | 21,22,23,24,25,26,27,28,29,30,14,15,16,17,18,19,20,21,22,23 | 17 | 3 | 15% |
### String Hash 
| table sizes (m) | Key Indices | **unique indices** | **collisions** | **collision rate** |
|------------------|------------|-----------------|------------|------------|
| **m=10** | 0,0,0,0,0,0,0,0,0,0 | 1 | 9 | 90% |
| **m=11** | 0,0,0,0,0,0,0,0,0,0 | 1 | 9 | 90% |
| **m=37** | 0,0,0,0,0,0,0,0,0,0 | 1 | 9 | 90% |
 ---
## Multiplication Method
 - h(k) = floor(m*(k*A mod 1)), 0 < A < 1 (研究顯示A 約 0.618時效果最好)
### Integer Hash 
| table sizes (m) | Key Indices | **unique indices** | **collisions** |**collision rate** |
|------------------|------------|-----------------|------------|------------|
| **m=10** | 9,5,2,8,4,0,6,3,9,5,5,1,7,3,9,6,2,8,4,0 | 10 | 10 | 50% |
| **m=11** | 10,6,2,9,4,0,7,3,10,5,5,1,8,4,10,6,2,9,5,0 | 11 | 9 | 45% |
| **m=37** | 36,22,7,30,16,2,25,11,34,19,19,5,27,13,36,22,8,31,17,2 | 16 | 4 | 20% |
### String Hash 
| table sizes (m) | Key Indices | **unique indices** | **collisions** | **collision rate** |
|------------------|------------|-----------------|------------|------------|
| **m=10** | 9,9,0,9,1,2,3,3,8,2 | 6 | 4 | 40% |
| **m=11** | 10,10,0,10,1,2,4,3,9,3 | 7 | 3 | 30% |
| **m=37** | 33,36,0,36,6,8,14,12,30,10 | 9 | 1 | 10% |