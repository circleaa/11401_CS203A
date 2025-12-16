# 資料結構筆記
這份筆記整理了常見的基本資料結構與其特性、操作

---
- [Array + Linked List 筆記](Array_LinkedList.md)
- [Stack + Queue 筆記](Stack_Queue.md)
- [Hashing 筆記](Hashing.md)
- [Tree 筆記](Tree.md)
- [Graph 筆記](Graph.md)

### Array、Linked List、Stack、Queue 的 ADT 操作與特性比較

| 操作 / 資料結構 | **Array** | **Linked List** | **Stack** | **Queue** |
|------------------|------------|-----------------|------------|------------|
| **ADT 定義** | 有序元素集合，可用index直接存取 | 節點以pointer串接形成序列 | 後進先出（LIFO）結構 | 先進先出（FIFO）結構 |
| **存取方式** | 隨機存取 (Random Access) | 順序存取 (Sequential Access) | 只能存取頂端 | 只能存取前端 / 後端 |
| **插入 (Insert)** | 指定位置插入：O(n) | 指定節點後插入：O(1) | `push(x)`：O(1) | `enqueue(x)`：O(1) |
| **刪除 (Delete)** | 指定位置刪除：O(n) | 移除節點：O(1) | `pop()`：O(1) | `dequeue()`：O(1) |
| **存取 (Access)** | `get(i)`：O(1) | 遍歷節點：O(n) | `top()`：O(1) | `front()`：O(1) |
| **搜尋 (Search)** | 線性搜尋 O(n)，若排序可二分搜尋 O(log n) | 順序搜尋 O(n) | 須遍歷整個stack O(n) | 須遍歷整個queue O(n) |
| **排序 (Sort)** | O(n log n)，可原地排序 | O(n log n)，但操作較慢 | ❌ | ❌ |
| **是否支援隨機存取** | ✅ | ❌ | ❌ | ❌ |
| **是否可動態擴充** | 若為 vector 可 ✅ | ✅ | ✅（用 Linked List 實作） | ✅（用 Linked List 實作） |
| **記憶體效率** | 連續空間、高 cache 效率 | 需額外指標開銷 | 中等 | 中等 |
| **應用** | 排序、查找、矩陣運算 | 動態資料、模組化結構 | 函式呼叫、回溯 | 排程、佇列任務 |
| **優點** | 快速隨機存取 | 插入刪除靈活 | 操作簡單、固定規則 | 適合排隊系統 |
| **缺點** | 插入刪除慢、大小固定 | 需額外指標、cache 效率低 | 只能操作頂端 | 只能操作兩端 |

