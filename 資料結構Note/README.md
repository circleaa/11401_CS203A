# 資料結構筆記
這份筆記整理了常見的基本資料結構與其特性與操作

---

## Array（陣列）
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

## Linked List（鏈結串列）

由多個節點（node）組成，每個節點包含資料與下一個節點的指標

### 結構特性
- 不連續記憶體配置，每個節點獨立配置
- 插入與刪除節點只需改變指標（O(1)）
- 不支援隨機存取，需從頭開始找（O(n)）

### 種類
- **Singly Linked List（單向鏈結串列）**：每個節點指向下一個節點
- **Doubly Linked List（雙向鏈結串列）**：節點有前後指標
- **Circular Linked List（循環鏈結串列）**：最後一個節點指回第一個節點

# ⏱ Array vs Linked List 時間複雜度比較

| 操作類型 | Array (陣列) | Linked List (鏈結串列) | 說明 |
|-----------|---------------|------------------------|------|
| **存取 (Access)** | O(1) | O(n) | Array 可透過索引直接存取，Linked List 需從頭遍歷 |
| **搜尋 (Search)** | O(n) | O(n) | 都需要線性搜尋（除非 Linked List 已排序並用特別方法） |
| **插入 (Insert)** | O(n) | O(1) | Array 中間插入需搬移元素，Linked List 只需改指標 |
| **刪除 (Delete)** | O(n) | O(1) | Array 中間刪除需搬移元素，Linked List 只需改指標 |
| **插入/刪除頭尾** | 插入尾部 O(1)（dynamic array 可 amortized O(1)）<br>刪除尾部 O(1) | 頭部插入/刪除 O(1)，尾部需遍歷 O(n) (Singly Linked List) | 頭尾操作差異明顯，Stack/Queue 可用 Linked List 高效實作 |

---

## Stack（堆疊）

後進先出（**LIFO, Last In First Out**）的結構

### 主要操作
- `push(x)`：將元素放入堆疊頂端  
- `pop()`：移除堆疊頂端的元素  
- `top()` / `peek()`：查看頂端元素但不移除  

### 實作方式
- **Array-based Stack**：用陣列實作
- **Linked-list Stack**：用鏈結串列實作  

### 應用
- 函式呼叫（呼叫堆疊）
- 括號匹配
- 遞迴展開與回溯

---

## Queue（佇列）

先進先出（**FIFO, First In First Out**）的結構

### 主要操作
- `enqueue(x)`：在尾端加入元素  
- `dequeue()`：從前端移除元素  
- `front()` / `peek()`：查看最前端元素  

### 實作方式
- **Array-based Queue**：固定大小，可配合「循環佇列」解決空間浪費  
- **Linked-list Queue**：用指標連接節點  

### 應用
- 作業排程（CPU queue）
- 印表機工作列隊
- BFS（廣度優先搜尋）

---
