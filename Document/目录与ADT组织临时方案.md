# 目录与 ADT 组织临时方案

更新时间：2026-04-06

## 一、目的

记录当前阶段对项目目录组织和 ADT 分层方式的临时设计结论。

这份文档的定位是：

- 作为后续持续维护时的阶段性组织依据
- 约束新增数据结构的目录归属
- 说明目录分类与 ADT 分类的边界

这不是最终定稿，后续可随着学习推进继续修订。

## 二、当前约束

本轮方案遵循以下前提：

- 文件名、目录名尽量沿用当前项目命名方式
- 继续使用 `Linear_Structure`、`Tree_Structure`、`Graph_Structure`、`Set_Structure` 一类命名
- 不再新增“所有树共用”的顶层 `ADT`
- 正式 ADT 文档继续放在 `Document/ADT/`
- 过程性记录继续放在 `Document/Codex/`

## 三、组织原则

### 1. 目录按对外语义归类

目录归属优先看该结构对外提供的核心操作，而不是优先看其底层长得像什么。

例如：

- `Heap` 的核心语义是优先队列，不是普通树
- `MergeFindSet` 的核心语义是不相交集合，不是普通树

### 2. ADT 按结构家族分别定义

后续只保留“家族级 ADT”，不保留“总的数据结构 ADT”或“总的树 ADT”。

例如：

- `Linear_List` 有自己的 ADT
- `Tree_Binary` 有自己的 ADT
- `Tree_Binary_Search` 有自己的 ADT
- `MergeFindSet` 有自己的 ADT
- `Priority_Queue` 有自己的 ADT

### 3. 存储表示法不进入上层总分类

例如普通树的：

- 双亲表示法
- 孩子表示法
- 孩子兄弟表示法

这些属于同一类树结构的不同实现，不应单独上升为顶层分类。

### 4. 输出、调试、演示不进入 ADT

ADT 只描述公共逻辑语义，不把以下内容写入公共契约：

- `Show`
- `Print`
- `std::cout` 输出
- Demo 专用构造逻辑

## 四、当前确认的目录组织方向

当前进一步确认：

- C++ 代码后续以顶级 `Structure/` 目录作为组织基点
- 中间层先表达 ADT 家族
- 末端实现层再体现存储结构特点
- 末端文件名后续可继续调整，本阶段先不固定

## 五、推荐的 C++ 目录案例

在保持当前命名风格的前提下，当前记录的目录案例为：

```text
Data_Sturcture/C++/
├── Structure/
│   ├── Linear/
│   │   ├── List/
│   │   │   ├── ADT.hpp
│   │   │   ├── List.hpp
│   │   │   ├── Sequential_List/
│   │   │   └── Link_List/
│   │   ├── Stack/
│   │   │   ├── ADT.hpp
│   │   │   ├── Stack.hpp
│   │   │   ├── Sequential_Stack/
│   │   │   └── Link_Stack/
│   │   └── Queue/
│   │       ├── ADT.hpp
│   │       ├── Queue.hpp
│   │       ├── Sequential_Queue/
│   │       └── Link_Queue/
│   ├── Tree/
│   │   ├── Normal/
│   │   │   ├── ADT.hpp
│   │   │   ├── Tree.hpp
│   │   │   ├── Parent_Array/
│   │   │   ├── Child_LinkList/
│   │   │   └── ChildSibling_Link/
│   │   ├── Binary/
│   │   │   ├── ADT.hpp
│   │   │   ├── Tree.hpp
│   │   │   ├── Link_BinaryTree/
│   │   │   └── Thread_BinaryTree/
│   │   ├── Search/
│   │   │   ├── ADT.hpp
│   │   │   ├── Tree.hpp
│   │   │   ├── Binary_Search_Link/
│   │   │   ├── AVL_Link/
│   │   │   └── RedBlack_Link/
│   │   ├── Multiway/
│   │   │   ├── ADT.hpp
│   │   │   ├── Tree.hpp
│   │   │   ├── B_Tree/
│   │   │   └── BPlus_Tree/
│   │   ├── String/
│   │   │   └── Trie_Link/
│   │   ├── Range/
│   │   │   ├── Segment_Sequential/
│   │   │   └── Fenwick_Sequential/
│   │   └── Spatial/
│   │       └── R_Tree/
│   ├── Graph/
│   │   ├── ADT.hpp
│   │   ├── Graph.hpp
│   │   ├── Matrix_Graph/
│   │   ├── AdjacencyList_Graph/
│   │   └── EdgeSet_Graph/
│   ├── Set/
│   │   ├── ADT.hpp
│   │   ├── Set.hpp
│   │   ├── HashSet_OpenAddressing/
│   │   ├── HashSet_LinkAddress/
│   │   └── MergeFindSet_ParentArray/
│   └── Priority/
│       ├── ADT.hpp
│       ├── Queue.hpp
│       ├── BinaryHeap_Sequential/
│       └── LeftistHeap_Link/
├── Algorithms/
├── Test/
└── Readme.md
```

当前这份目录案例强调两条：

- `Structure/` 负责统一承载各类数据结构代码
- 末端实现目录用来表达存储结构特征，例如 `Sequential_List`、`Parent_Array`、`Matrix_Graph`

## 六、目录命名的当前约定

### 1. 中间层目录避免冗余

例如：

- 使用 `Tree/Normal`
- 不使用 `Tree/Tree_Normal`

### 2. 末端实现目录体现存储结构

例如：

- `Sequential_List`
- `Link_List`
- `Parent_Array`
- `Child_LinkList`
- `ChildSibling_Link`
- `Matrix_Graph`
- `AdjacencyList_Graph`

这类命名的目的不是重复 ADT 名称，而是补充实现方式信息。

### 3. 末端文件名暂不在本轮固定

当前只先记录目录层级案例。

后续在具体迁移某个模块时，再决定末端目录中是否采用：

- `Tree.hpp` / `Node.hpp`
- 或更细的专用文件名

## 七、各目录的语义边界

### 1. `Linear`

保留线性逻辑关系的数据结构：

- `Linear_List`
- `Linear_Stack`
- `Linear_Queue`

### 2. `Tree`

只放“对外语义就是树”的结构家族：

- `Normal`
- `Binary`
- `Search`
- `Multiway`
- `String`
- `Range`
- `Spatial`

其中：

- `Normal` 对应普通树 / 多叉树
- `Binary` 对应普通二叉树 / 线索二叉树
- `Search` 对应 BST / AVL / Red-Black Tree
- `Multiway` 对应 B-Tree / B+Tree
- `String` 对应 Trie / Radix Tree
- `Range` 对应 Segment Tree / Fenwick Tree
- `Spatial` 对应 R-Tree / KD-Tree

### 3. `Graph`

保留图的逻辑结构与图算法承载结构：

- 邻接矩阵
- 邻接表
- 边集数组

### 4. `Set`

放“集合语义”相关结构：

- `Set`
- `MergeFindSet`
- `Hash_Table`

这里的结论是：

- `MergeFindSet` 长期应归入 `Set`
- 不再视为 `Tree` 的一部分

### 5. `Priority`

单独承载优先队列语义。

这里的结论是：

- `Heap` 长期应归入 `Priority`
- 即使其常见实现是完全二叉树，也不作为普通树 ADT 处理

## 八、推荐的 ADT 文档组织

正式 ADT 文档继续放在 `Document/ADT/`，推荐逐步整理为：

```text
Document/ADT/
├── Linear_Structure/
│   ├── Linear_List.md
│   ├── Stack.md
│   └── Queue.md
├── Tree_Structure/
│   ├── Tree.md
│   ├── Tree_Binary.md
│   ├── Tree_Binary_Search.md
│   ├── Tree_Multiway_Search.md
│   ├── Tree_String.md
│   ├── Tree_Range.md
│   └── Tree_Spatial.md
├── Graph_Structure/
│   └── Graph.md
├── Set_Structure/
│   ├── Set.md
│   └── MergeFindSet.md
└── Priority_Structure/
    └── Priority_Queue.md
```

其中：

- `Tree.md` 继续表示普通树 ADT
- `Tree_Binary.md` 表示二叉树 ADT
- `Tree_Binary_Search.md` 表示二叉搜索树 ADT
- `MergeFindSet.md` 长期应转为 `Set_Structure/`
- 新增 `Priority_Queue.md` 用于承接 `Heap` 的公共语义

## 九、推荐的代码内 ADT 分层规则

后续每个结构家族内部，代码层推荐遵循以下约定：

### 1. `XXX.hpp`

用于承载当前实际使用的逻辑抽象层或共享基础类。

例如：

- `Linear_List.hpp`
- `Tree_Binary.hpp`
- `Tree_Binary_Search.hpp`

### 2. `ADT.hpp`

用于承载接口约束层。

优先用途：

- `concept`
- 接口检查
- 编译期约束

不再用于承载“大而全”的旧式总虚函数接口。

### 3. 具体实现目录

每个 ADT 下的不同实现继续放在各自子目录中。

例如：

- 顺序表 / 链表
- 普通 BST / AVL / Red-Black Tree
- 孩子表示法 / 双亲表示法 / 孩子兄弟表示法

## 十、关于 Heap 和 MergeFindSet 的阶段结论

### 1. Heap

阶段结论：

- 可承认其实现上属于树形实现
- 但项目组织上按 `Priority` 处理
- 不并入普通树 ADT 体系

### 2. MergeFindSet

阶段结论：

- 可承认其实现上常表现为森林
- 但项目组织上按 `Set` 处理
- 不并入普通树 ADT 体系

## 十一、过渡策略

由于当前仓库已经形成既有目录，后续建议按“先文档、后迁移”的顺序推进：

1. 先在文档中固定目录归属和 ADT 边界
2. 后续新增结构优先按本方案落位
3. 旧目录不立即大规模移动
4. 在需要重构某一模块时，再局部迁移到目标目录

## 十二、当前不再采用的做法

以下做法当前不再推荐继续扩大使用：

- 继续维护总的 `Tree_Structure/ADT.hpp` 作为所有树的统一父接口
- 把 `Heap` 继续视作普通树 ADT 的一个分支
- 把 `MergeFindSet` 继续视作普通树 ADT 的一个分支
- 按“节点底层长得像树”决定目录归属

## 十三、当前临时结论

当前项目后续维护的推荐方向可以概括为：

- 顶层代码目录以 `Structure/` 为组织基点
- 目录分类以对外语义为主
- ADT 按结构家族分别定义
- 末端实现目录体现存储结构特点
- 不再设置总的树 ADT
- `Heap` 向 `Priority` 收口
- `MergeFindSet` 向 `Set` 收口

这份文档先作为当前阶段的临时设计记录，后续如目录迁移正式开始，再补充迁移清单与落地规则。
