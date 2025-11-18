# Homework Assignment IV: Hash Function Design & Observation (C/C++ Version)

This assignment focuses on the design and observation of hash functions using C/C++. 
Students are expected to implement and analyze the behavior of hash functions, 
evaluate their efficiency, and understand their applications in computer science.

 - Developer: Yu-Jia Wang 王郁佳 
 - Email: <s1121430@mail.yzu.edu.tw> / <ariel940814@gmail.com>  

## My Hash Function
### Integer Keys 
- Formula / pseudocode:
  ```text
    const double A = 0.618; // 黃金比例倒數
    double frac = (key * A)- floor(key * A); //只取小數部分不然數值太大
    return int(m * frac);
  ```
- Rationale: h(k) = floor(m*(k*A mod 1)), 0 < A < 1 (研究顯示A 約 0.618時效果最好)

### Non-integer Keys
- Formula / pseudocode:
  ```text
    unsigned long hash = 0;
    const int base = 31;
    double A = 0.168;
    for (char c : str) //把字串轉成數字
        hash = hash * base + c; 
    double frac = hash*A - floor(hash*A); //取小數部分
    return int (m * frac);
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
| Table Size (m) | Index Sequence | Unique Indices | Collisions | **Collision Rate** | **Observation** |
|----------------|----------------|-----------------|------------|----------------|-------------|
| m=10 | 1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0 | 10 | 10 | **50%** | **Pattern repeats every 10** |
| m=11 | 10,0,1,2,3,4,5,6,7,8,7,8,9,10,0,1,2,3,4,5 | 11 | 9 | **45%** | **More uniform** |
| m=37 | 21,22,23,24,25,26,27,28,29,30,14,15,16,17,18,19,20,21,22,23 | 17 | 3 | **15%** | **Near-uniform** |
 - String Hash  
| Table Size (m) | Index Sequence | Unique Indices | Collisions | **Collision Rate** | **Observation** |
|----------------|----------------|-----------------|------------|----------------|-------------|
| m=10 | 0,0,0,0,0,0,0,0,0,0 | 1 | 9 | **90%** | **all zero** |
| m=11 | 0,0,0,0,0,0,0,0,0,0 | 1 | 9 | **90%** | **all zero** |
| m=37 | 0,0,0,0,0,0,0,0,0,0 | 1 | 9 | **90%** | **all zero** |
 ---
### Multiplication Method -> h(k) = floor(m*(k*A mod 1))
 - Integer Hash  
| Table Size (m) | Index Sequence | Unique Indices | Collisions | **Collision Rate** | **Observation** |
|----------------|----------------|-----------------|------------|----------------|-------------|
| **m=10 | 9,5,2,8,4,0,6,3,9,5,5,1,7,3,9,6,2,8,4,0 | 10 | 10 | **50%** | **Pattern repeats every 10** |
| m=11** | 10,6,2,9,4,0,7,3,10,5,5,1,8,4,10,6,2,9,5,0 | 11 | 9 | **45%** | **More uniform** |
| m=37 | 36,22,7,30,16,2,25,11,34,19,19,5,27,13,36,22,8,31,17,2 | 16 | 4 | **20%** | **Near-uniform** |
 - String Hash  
| Table Size (m) | Index Sequence | Unique Indices | Collisions | **Collision Rate** | **Observation** |
|----------------|----------------|-----------------|------------|----------------|-------------|
| m=10 | 9,9,0,9,1,2,3,3,8,2 | 6 | 4 | **40%** | **Near-uniform** |
| m=11 | 10,10,0,10,1,2,4,3,9,3 | 7 | 3 | **30%** | **Near-uniform** |
| m=37 | 33,36,0,36,6,8,14,12,30,10 | 9 | 1 | **10%** | **Near-uniform** |

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
- Example output for integers:
  ```
  === Hash Function Observation (C Version) ===

  === Table Size m = 10 ===
  Key     Index
  -----------------
  21      1
  22      2
  ...

  === Table Size m = 11 ===
  Key     Index
  -----------------
  21      10
  22      0
  ...

  === Table Size m = 37 ===
  Key     Index
  -----------------
  21      21
  22      22
  ...

  === Hash Function Observation (C++ Version) ===

  === Table Size m = 10 ===
  Key     Index
  -----------------
  21      1
  22      2
  ...

  === Table Size m = 11 ===
  Key     Index
  -----------------
  21      10
  22      0
  ...

  === Table Size m = 37 ===
  Key     Index
  -----------------
  21      21
  22      22
  ...
  ```

- Example output for strings:
  ```
  === String Hash (m = 10) ===
  Key     Index
  -----------------
  cat     0
  dog     0
  ...

  === String Hash (m = 11) ===
  Key     Index
  -----------------
  cat     0
  dog     0
  ...

  === String Hash (m = 37) ===
  Key     Index
  -----------------
  cat     0
  dog     0
  ...
  ```

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