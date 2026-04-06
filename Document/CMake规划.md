# CMake 规划

更新时间：2026-04-06

## 一、定位

本文件用于记录仓库后续 `CMake` 的目标形态和推进方向。

它解决的问题不是“当前怎么临时编过”，而是：

- 最终希望把仓库整理成什么样
- 各层 `CMakeLists.txt` 的职责怎么划分
- 哪些目录进入主线，哪些目录只保留参考价值
- 后续完善时应按什么顺序推进

## 二、总体目标

仓库的 `CMake` 最终应同时满足以下目标：

1. 顶层职责清晰
2. `Data_Sturcture/C++` 形成可持续演进的主线
3. `Data_Sturcture/C` 保持为可构建的参考实现
4. Demo、UnitTest、Reference 的输出目录统一
5. 测试可通过 `CTest` 统一执行
6. 未完成模块不会拖垮主线构建

## 三、主线与参考线

### 1. `Data_Sturcture/C++`

定位：

- 主线实现
- 后续持续整理和演进的重点
- 当前优先级最高

要求：

- 可按模块逐步接入
- 可统一构建 Demo
- 可统一构建 UnitTest
- 可通过 `ctest` 执行测试

### 2. `Data_Sturcture/C`

定位：

- 参考实现
- 用于保留早期思路、可运行示例和对照实现
- 不作为当前主线持续治理对象

要求：

- 可单独配置
- 可单独构建
- 有清晰的参考入口
- 不影响 `C++` 主线整理

### 3. 其他目录

当前暂不纳入主线 CMake 规划范围：

- `Data_Sturcture/Experimental`
- `Data_Sturcture/Library_C++`
- `QT`

这些目录后续是否处理，单独讨论。

## 四、顶层 CMake 的最终职责

顶层 CMakeLists.txt 最终只负责以下内容：

1. 设置全局 C++ 标准
2. 设置全局输出目录
3. 定义全局开关
4. 引入 `CTest`
5. 进入 `Data_Sturcture`

不应在顶层直接承担模块级细节逻辑。

## 五、建议的开关设计

当前或后续建议使用的开关如下：

### 第一层：主线/参考线选择

- `Build_CPP`
- `Build_C_Reference`

说明：

- `Build_CPP` 控制 `Data_Sturcture/C++`
- `Build_C_Reference` 控制 `Data_Sturcture/C`
- 二者应允许独立开启

### 第二层：用途开关

- `BUILD_DEMOS`
- `BUILD_TESTING`

说明：

- `BUILD_DEMOS` 控制是否构建示例程序
- `BUILD_TESTING` 控制是否构建并注册测试

### 第三层：模块开关

当前已经实现或正在使用的模块开关包括：

- `BUILD_ALGORITHMS`
- `BUILD_GRAPH_STRUCTURE`
- `BUILD_SET_STRUCTURE`
- `BUILD_TREE_STRUCTURE`

说明：

- `BUILD_GRAPH_STRUCTURE=OFF`
- `BUILD_TREE_STRUCTURE=OFF`

目前这两个开关默认关闭，用来避免未收敛模块以“显式模块启用”的方式拖垮默认主线。
但当前 `BUILD_TESTING=ON` 时，图和树目录仍会为了测试接入而被加入构建图。

后续如果线性结构也需要单独开关，再考虑加入：

- `BUILD_LINEAR_STRUCTURE`

## 六、输出目录规划

构建目录默认使用：

```bash
cmake -S . -B Build
```

最终产物目录按用途区分：

- `Build/bin/Demo/`
- `Build/bin/UnitTest/`
- `Build/bin/Reference/`
- `Build/lib/`

规则：

1. 目录表达用途
2. 文件名表达模块名
3. 不用文件名前缀重复表达用途

示例：

- `Build/bin/Demo/Sequential_List`
- `Build/bin/UnitTest/Sequential_List`
- `Build/bin/Reference/Data_Structure_C`

不推荐：

- `Build/bin/Demo/Demo_Sequential_List`
- `Build/bin/UnitTest_Sequential_List`

## 七、目标命名策略

建议区分“内部 target 名”和“最终输出名”。

### 1. 内部 target 名

用于避免冲突，应尽量唯一且可读，例如：

- `ds_cpp_linear_list_sequential_demo`
- `ds_cpp_linear_list_sequential_unit_test`
- `ds_c_reference_main`

### 2. 最终输出名

用于展示给使用者，只保留模块名，例如：

- `Sequential_List`
- `Link_List`
- `Data_Structure_C`

这样可以同时满足：

- CMake 内部组织清晰
- 产物文件名整洁

## 八、目录职责规划

### 1. `Cmake/`

后续应逐步承担公共辅助逻辑，例如：

- 创建 demo 目标的辅助函数
- 创建 unit test 目标的辅助函数
- 设置统一 include 目录
- 设置统一输出目录

### 2. `Data_Sturcture/C++/各模块目录`

各模块目录应只声明：

- 本模块有哪些实现
- 本模块有哪些 demo
- 本模块有哪些 unit test

不应重复书写过多通用规则。

### 3. `Data_Sturcture/C++/Test`

测试源码可以继续按模块分布，但 `CMake` 侧应负责：

- 统一链接 `Boost.Test`
- 统一注册到 `CTest`
- 统一设置测试目标输出目录

## 九、模块纳管分层

后续 `Data_Sturcture/C++` 中的模块建议分三层管理：

### 1. stable

特点：

- 默认纳入主线构建
- 默认纳入 demo
- 默认纳入 unit test

### 2. experimental

特点：

- 可以构建
- 不一定默认启用
- 测试可能不完整

### 3. excluded

特点：

- 当前不纳入主线
- 不参与默认构建
- 等后续条件成熟再接入

这样可以避免因为个别未完成模块影响整个主线。

## 十、测试相关的 CMake 目标

`CMake` 对测试部分的职责应保持克制，只负责：

1. 构建测试目标
2. 注册到 `CTest`
3. 提供统一输出目录
4. 提供必要的全局测试开关

测试语义层面的分层暂定为：

- ADT 契约测试
- 实现特性测试
- 回归测试

这部分已记录在 [测试完善规划.md](测试完善规划.md)，但当前不是优先实现项。

## 十一、当前样板策略

当前不直接大面积接模块，而采用“最小完整样板复制”的方法。

样板要求：

1. 至少包含一个源码示例入口
2. 至少包含一个单元测试入口
3. 能进入统一输出目录
4. 能被 `CTest` 发现并执行

补充说明：

- 最初样板模块是 `Sequential_List`
- 当前已经从单一样板扩展到 `Link_List`、`Sequential_Stack`、`Link_Stack`、`Sequential_Queue`、`Link_Queue` 等基础模块
- 默认主线已经具备真实 `build + ctest` 验证能力，后续重点不再是“样板能不能跑”，而是“哪些模块可以稳定纳入默认集合”

当前已打通样板：

- `Sequential_List`
- `Link_List`
- `Sequential_Stack`
- `Sequential_Queue`
- `Link_Queue`
- `Link_Stack`

后续建议优先接入：

1. `MergeFindSet`
2. `Tree_Binary_Search`
3. `Graph_AdjacencyList`

## 十二、推进顺序

后续建议按以下顺序推进：

1. 继续接更多 `C++` 样板模块
2. 验证当前模式可复制
3. 逐步扩充公共 `Cmake/*.cmake` 规则
4. 增加用途级开关
5. 逐步做模块纳管分层
6. 再处理树、图、集合等更复杂模块

## 十三、阶段性原则

后续推进 `CMake` 时遵守以下原则：

1. 优先建立可维护的结构，而不是一次性接入所有目录
2. 先保证 `C++` 主线稳定，再逐步扩大覆盖面
3. `C` 参考线要求“可构建”，不要求“按主线标准治理”
4. 输出目录和命名规则一旦确定，尽量不要频繁变动
5. 公共规则在样板数量足够后再抽取，避免过早抽象

## 十四、当前结论

关于 `CMake` 的长期方向，当前已形成的共识是：

> `Data_Sturcture/C++` 作为主线逐步工程化；
> `Data_Sturcture/C` 作为参考实现独立保留；
> 先用少量样板模块建立稳定模式，再逐步扩展到整个主线。

## 十五、当前已落地内容

截至目前，以下内容已实现：

1. `Sequential_List` 已完成 Demo / UnitTest / `CTest` 接入
2. `Link_List` 已完成 Demo / UnitTest / `CTest` 接入
3. `Sequential_Stack` 已完成 Demo / UnitTest / `CTest` 接入
4. `Sequential_Queue` 已完成 Demo / UnitTest / `CTest` 接入
5. `Link_Queue` 与 `Link_Stack` 已完成 Demo / UnitTest / `CTest` 接入
6. `MergeFindSet`、`Tree_Binary_Search`、`Tree_Binary`、`Graph_AdjacencyList` 已接入行为测试
7. 已引入最小公共辅助模块 [DataStructureTargets.cmake](Cmake/DataStructureTargets.cmake)
8. 已启用用途级开关 `BUILD_DEMOS`
9. `Algorithms / Graph_Structure / Set_Structure / Tree_Structure` 已进入 `CMake` 组织范围
10. 当前默认 `ctest` 已稳定执行 `24` 个测试
11. 剩余 demo 与 unit test 入口已批量接入，但仍需继续按模块验证和收敛

当前说明：

- 样板数量已经超过早期 4 个基础模块阶段
- 当前模式已经证明可以复制
- 当前已从“样板阶段”进入“批量接入 + 回归扩面阶段”
- 后续重点会转向收敛未验证模块、整理分层、同步文档与增强公共 CMake 抽象

## 十六、默认主线验证状态

当前默认主线验证已完成，验证命令为：

```bash
cmake -S . -B Build
cmake --build Build
ctest --test-dir Build --output-on-failure
```

验证结果：

- `configure` 通过
- `build` 通过
- `ctest` 执行 24 项测试，全部通过

当前默认开关状态为：

- `BUILD_ALGORITHMS=ON`
- `BUILD_SET_STRUCTURE=ON`
- `BUILD_GRAPH_STRUCTURE=OFF`
- `BUILD_TREE_STRUCTURE=OFF`

这样设置的原因是：

- `BUILD_GRAPH_STRUCTURE` 与 `BUILD_TREE_STRUCTURE` 仍用于控制显式模块启用范围
- 图结构 demo 仍处于 experimental 路线，不适合直接视为默认稳定 demo 集合
- 树结构中已有一部分稳定 demo 和行为测试能在当前默认主线中构建
- 当前图/树测试是通过 `BUILD_TESTING=ON` 接入默认回归，而不是通过把模块开关全部打开来实现

因此，当前采用的策略是：

1. 先保证默认主线构建稳定可用
2. 将 `Graph_Structure` 和 `Tree_Structure` 保留为“显式模块开关默认关闭，但允许测试路径先纳入主线”的状态
3. 后续再单独逐步收敛图/树剩余 demo 和未完成实现的构建问题
