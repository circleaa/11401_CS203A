## Stack
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

## Queue

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

# Stack / Queue：Array vs Linked List 實作比較

| 實作方式 | 記憶體配置 | 主要操作時間複雜度 | 優點 | 缺點 |
|-----------|------------|----------------------|------|------|
| **Stack (Array-based)** | 連續記憶體（固定或動態陣列） | `push` / `pop`：O(1) | 實作簡單、存取快、cache 效率高 | 大小需預先設定（static array）或需重新配置（dynamic array） |
| **Stack (Linked List-based)** | 分散記憶體（節點用指標相連） | `push` / `pop`：O(1) | 不需預先知道大小、插入刪除靈活 | 額外指標記憶體開銷大、cache 效率差 |
| **Queue (Array-based)** | 連續記憶體 | `enqueue` / `dequeue`：O(1)（若使用循環佇列） | 結構簡單、易於管理 | 若不使用循環佇列會造成空間浪費；動態擴展麻煩 |
| **Queue (Linked List-based)** | 分散記憶體 | `enqueue` / `dequeue`：O(1) | 動態大小，不需搬移元素 | 額外指標開銷、cache 效率差 |

---
