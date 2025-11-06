## Array
一塊**連續的記憶體空間**，用索引（index）存取元素。

### 結構特性
- **隨機存取**：可直接透過索引取得元素（O(1)）
- **插入/刪除慢**：中間插入或刪除需要搬移元素（O(n)）

### Size 類型
- **Static Array**：元素數量在編譯時固定
- **Dynamic Array**：可在執行時調整大小

### Sorting
- **Bubble Sort**：比較相鄰兩個元素，若順序錯誤則交換（swap）
- **Selection Sort**：選出剩餘元素中的最小值移到前面（swap）
- **Insertion Sort**：新元素向前比較，插入到正確位置

---

## Linked List

由多個節點（node）組成，每個節點包含資料與下一個節點的指標

### 結構特性
- 不連續記憶體配置，每個節點獨立配置
- 插入與刪除節點只需改變指標（O(1)）
- 不支援隨機存取，需從頭開始找（O(n)）

### 種類
- **Singly Linked List（單向鏈結串列）**：每個節點指向下一個節點
- **Doubly Linked List（雙向鏈結串列）**：節點有前後指標
- **Circular Linked List（循環鏈結串列）**：最後一個節點指回第一個節點

---

### Array vs Linked List 時間複雜度比較

| 操作類型 | Array | Linked List | 說明 |
|-----------|---------------|------------------------|------|
| **Access** | O(1) | O(n) | Array 可透過索引直接存取，Linked List 需從頭訪問 |
| **Search** | O(n) | O(n) | 都需要線性搜尋 |
| **Insert** | O(n) | O(n) | Array 中間插入需搬移元素，Linked List 只需改指標 |
| **Insert at front** | O(n) | O(1) | Linked List 有 head 指標 |
| **Insert at end** | O(1) | O(n) | 若 Linked List 使用 tail(尾指標)就只需 O(1) |
| **Delete** | O(n) | O(n) | 若 Linked List 已知 node pointer 就只需O(1) |
| **Find minimum** | O(n) | O(n) | 都需 scan 所有元素 |
| **Swap** | O(1) | O(1) | Linked List swap by values |
| **Traversal between elements** | O(1) | O(n) | Linked List 需用 pointer |

---

### Array vs Linked List 其他比較

| 特性 | Array | Linked List |
|-----------|---------------|------------------------|
| **Memory allocation** | 連續 memory 區塊 | 不連續，nodes 動態分配 |
| **Size** | 固定 | 可在 runtime 時增/減 |
| **Access** | 直接由 index 訪問 O(1) | 依序訪問 O(n) | 
| **額外 variables** | i, j, min_idx, MAX_SIZE | head, current, next, min_node |
| **Traversal** | 快 | 慢(非連續區塊，要用 pointers) |
| **Overhead** | 小的 memory 開銷 | 需額外的 memory 給 pointers |
| **Flexibility** | Fixed size(需 reallocation) | Dynamic size(容易 insert/delete) |
| **Overall** | 適合固定大小和頻繁訪問 | 適合頻繁上傳動態資料 |
