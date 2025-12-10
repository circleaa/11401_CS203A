# Hashing（雜湊）

## 基本概念
**Hashing** 是一種透過「雜湊函式（hash function）」將**鍵值（key）**轉換成陣列索引（index）的方法。  
目的是在 **O(1)** 平均時間內完成插入、搜尋與刪除。

---

## Hash Function（雜湊函式）
將 key 映射成 table index 的函式： h(key) = key mod table_size

### 好的 Hash Function 特性：
- 分布均勻（Uniform Distribution）  
- 計算簡單快速  
- 避免 clustering（避免集中到某些位置）

---

## Collision（碰撞）
不同的 key 經過 hash function 可能得到相同的 index → **碰撞 (collision)**。  
常見解決方式如下：

| 方法 | 說明 | 優點 | 缺點 |
|------|------|------|------|
| **Chaining（鏈結法）** | 每個位置是一條 linked list，碰撞的元素加在同一串列中 | 簡單、靈活 | 額外記憶體開銷 |
| **Open Addressing（開放位址法）** | 若碰撞，依規則尋找下個空位 | 不需額外指標 | 需良好探查策略，可能產生 clustering |

---

## Open Addressing 探查法種類

| 探查法 | Hash Function 範例 | 說明 | 缺點 |
|--------|----------------------|------|------|
| **Linear Probing** | `(h(key) + i) mod m` | 依序往後探查 | 可能產生 primary clustering |
| **Quadratic Probing** | `(h(key) + c1·i + c2·i²) mod m` | 探查距離呈平方成長 | 需小心無限迴圈 |
| **Double Hashing** | `(h1(key) + i·h2(key)) mod m` | 使用第二個 hash function | 分布較均勻、效能佳 |

---

## Hash Table 操作複雜度（平均情況）

| 操作 | 平均時間複雜度 | 最壞情況 |
|------|------------------|-----------|
| Insert | O(1) | O(n) |
| Search | O(1) | O(n) |
| Delete | O(1) | O(n) |

> 若使用良好的 hash function 且載入因子適中（α < 0.7），通常可維持 O(1) 效能。
> Load Factor（載入因子）: hash table 填滿的程度，可決定查找速率。
