# 資料結構筆記
這份筆記整理了常見的基本資料結構與其特性與操作

---
- [Array 筆記](Array_LinkedList.md)

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
