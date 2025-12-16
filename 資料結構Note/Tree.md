# 樹 (Trees)

[cite_start]這份文件整理了樹 (Trees) 這種非線性階層式資料結構的核心概念、術語、類型和操作，主要依據 CS203A, COMPUTER SCIENCE & ENGINEERING 課程資料 (Yuan Ze University) [cite: 4, 61, 135]。

## 1. 核心定義與概念

* [cite_start]**定義**：樹是一種**非線性階層式資料結構**，由透過邊（Edges）連接的節點（Nodes）組成 [cite: 132]。
* **特性**：
    * [cite_start]每個節點可以有零個或多個子節點，形成父子關係 [cite: 133]。
    * [cite_start]樹中**沒有循環 (cycles)** [cite: 134]。
    * [cite_start]用於表示像檔案系統或組織結構這類的階層式關係 [cite: 134]。
* [cite_start]**樹在日常生活中的應用**[cite: 21]:
    * [cite_start]家族樹 (Family tree) [cite: 22, 29]。
    * [cite_start]檔案系統階層 (File system hierarchy) [cite: 23, 24]。

## 2. 樹的基本術語 (Terminology)

[cite_start]樹的基本元件包括節點 (root, internal, leaf, parent, child, sibling)、邊 (Edge)、子樹 (Subtree)、層級 (Level)、深度 (Depth) 和高度 (Height) [cite: 122, 123, 124, 125, 126, 127]。

| 術語 (Term) | 定義 (Definition) | 說明/關係 |
| :--- | :--- | :--- |
| **根節點 (Root)** | [cite_start]樹的最頂層節點 [cite: 188]。 | [cite_start]一棵樹只有一個根節點 [cite: 13]。 |
| **葉節點 (Leaf)** | [cite_start]沒有子節點的節點 [cite: 178, 188]。 | |
| **父節點 / 子節點** | [cite_start]父節點是具有指向其他節點分支的節點 [cite: 188]。 | [cite_start]形成父子關係 [cite: 133]。 |
| **兄弟節點 (Sibling)** | [cite_start]共享同一父節點的節點 [cite: 145, 188]。 | |
| **邊 (Edge)** | [cite_start]連接兩個節點的連線 [cite: 143, 188]。 | |
| **深度 (Depth)** | [cite_start]距離根節點的距離 [cite: 172, 188]。 | |
| **高度 (Height)** | [cite_start]到最遠葉節點的最長路徑 [cite: 150, 188]。 | |
| **分支度 (Fan-out)** | [cite_start]一個節點可以擁有的子節點數量 [cite: 154, 188]。 | |

## 3. 樹的類型 (Types of Trees)

### 3.1. [cite_start]樹的演化階層 (General to Specialized) [cite: 216, 238]

| Level | Name | Extra rule compared to previous level | Type of constraint |
| :--- | :--- | :--- | :--- |
| **1** | **樹 (Tree)** | [cite_start]僅是一個有根的階層結構，對子節點數量無限制 [cite: 239]。 | [cite_start]Very general shape [cite: 239]。 |
| **2** | **二元樹 (Binary Tree)** | [cite_start]每個節點最多有 2 個子節點 (left/right) [cite: 222, 239]。 | [cite_start]Shape constraint (arity) [cite: 239]。 |
| **3** | **二元搜尋樹 (BST)** | [cite_start]每個節點：左子樹 $<$ 節點 $<$ 右子樹 [cite: 226, 239, 651]。 | [cite_start]Ordering (search) invariant [cite: 239, 652]。 |
| **4** | **平衡 BST (AVL, Red-Black)** | [cite_start]高度保持在 $(\approx \log n)$ 附近 [cite: 234, 239, 1219]。 | [cite_start]Height / balance invariant [cite: 239, 1219]。 |

### 3.2. [cite_start]核心/基礎類型 [cite: 191]

| 類型 (Type) | 描述 (Description) | 應用 (Application) |
| :--- | :--- | :--- |
| **滿二元樹 (Full Binary Tree)** | [cite_start]每個節點都有 0 個或 2 個子節點 [cite: 201]。 | [cite_start]機器學習中的決策節點 [cite: 205]。 |
| **完全二元樹 (Complete Binary Tree)** | [cite_start]除最後一層外，所有層級都被填滿 [cite: 202]。 | [cite_start]堆積 (Heap) / 優先佇列 [cite: 206]。 |
| **AVL 樹** | [cite_start]高度差異 $\le 1$ [cite: 589, 1164]。 | [cite_start]快速查找 (Fast lookup) [cite: 589]。 |
| **紅黑樹** | [cite_start]透過顏色約束平衡 [cite: 589]。 | [cite_start]C++ STL map, Linux 核心 [cite: 589]。 |
| **字典樹 (Trie)** | [cite_start]基於字元的分支，快速字串檢索 [cite: 197, 202]。 | [cite_start]Dictionary words, auto-complete [cite: 208]。 |

### 3.3. [cite_start]進階類型 [cite: 212]

| 類型 (Type) | 描述 (Description) | 應用 (Application) |
| :--- | :--- | :--- |
| **B-Tree / B+ Tree** | [cite_start]為磁碟儲存設計的多路搜尋樹 [cite: 213]。 | [cite_start]資料庫、檔案系統 [cite: 213]。 |
| **堆積樹 (Heap Tree)** | [cite_start]是一種完全樹，父節點 $\ge$ 或 $\le$ 子節點 [cite: 213]。 | [cite_start]優先佇列 (Priority queue) [cite: 213]。 |
| **KD-Tree** | [cite_start]用於 k 維資料的空間分割 [cite: 213]。 | [cite_start]最近鄰搜尋 (ML) [cite: 213]。 |

## 4. 樹的遍歷 (Tree Traversal)

[cite_start]遍歷是按照特定順序訪問每個節點的過程 [cite: 243]。

### 4.1. 深度優先遍歷 (Depth-First Traversal, DFT)

| 順序 (Order) | 訪問序列 (Visit Sequence) | 用途 (Description) |
| :--- | :--- | :--- |
| **前序 (Preorder)** | [cite_start]根節點首先，然後是子節點 (Root-Left-Right) [cite: 296]。 | [cite_start]用於複製樹 (copying trees) [cite: 296]。 |
| **中序 (Inorder)** | [cite_start]左子樹、根節點、右子樹 (Left-Root-Right) [cite: 296]。 | [cite_start]對 BST 來說是排序後的順序 [cite: 296]。 |
| **後序 (Postorder)** | [cite_start]子節點首先，根節點最後 (Left-Right-Root) [cite: 296]。 | [cite_start]用於刪除或釋放記憶體 (deletion or freeing memory) [cite: 296]。 |

### 4.2. 廣度優先遍歷 (Breadth-First Traversal, BFT)

* [cite_start]也稱為：**層級順序遍歷 (Level-Order Traversal)** [cite: 325]。
* [cite_start]實現方式：逐層訪問節點，使用**佇列 (queue)** 實現 [cite: 325, 352]。

## 5. 二元搜尋樹 (BST) 的效能與操作

### 5.1. [cite_start]效能與平衡 [cite: 592]

* [cite_start]**問題**：如果 BST 變成**傾斜 (Skewed) / 退化 (Degenerate)**，搜尋和插入操作的複雜度會從 $O(\log n)$ 降級到 $O(n)$ [cite: 570, 1134]。
* [cite_start]**平衡 (Balance)**：維持 $\log$ 尺度的樹高，以確保效率 [cite: 592]。

| 操作 (Operation) | 平衡 BST (Balanced) | 傾斜 BST (Skewed/Worst-case) |
| :--- | :--- | :--- |
| **插入 (Insertion)** | [cite_start]$O(\log n)$ [cite: 1133] | [cite_start]$O(n)$ [cite: 1134] |
| **刪除 (Deletion)** | [cite_start]$O(\log n)$ [cite: 1144] | [cite_start]$O(n)$ [cite: 1145] |
| **遍歷 (Traversal)** | [cite_start]$O(n)$ [cite: 592] | [cite_start]$O(n)$ [cite: 592] |

### 5.2. [cite_start]內部節點刪除策略 (Two Children Case) [cite: 1141]

[cite_start]刪除具有兩個子節點的內部節點時，必須使用以下兩種替換選項之一，以保持 BST 屬性 ($left<parent<right$) [cite: 1119, 1125]。

1.  [cite_start]**選項 A**：用**左子樹中的最大值** (Max in left subtree) 替換 [cite: 1107][cite_start]。這被稱為**中序前驅 (inorder predecessor) (11)** [cite: 1125]。
2.  [cite_start]**選項 B**：用**右子樹中的最小值** (Min in right subtree) 替換 [cite: 1118][cite_start]。這被稱為**中序後繼 (inorder successor) (23)** [cite: 1125]。
