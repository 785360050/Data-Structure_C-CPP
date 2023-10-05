# 杂谈
1. 老版使用抽象类作为接口类，现在已经废弃，使用conecpt+static_assert检查接口规范，实现抽象数据类型
使用抽象类需要很多的template 参数，一个变化点一个参数,实现复杂。concept更灵活
所以取消了逻辑结构对接口类的继承，如：class Liner_List : public Liner_List_ADT<ElementType, DataType>
2. Clear需要对不同特性的模板类进行元编程，这里还不熟悉，晚点再看。暂时先限制元素类型都是非指针类型
3. 取消了逻辑结构的实例化，可以但意义不大，实际使用的应该是位于final的具体实现类
所以用namespace Logic集中管理,Logic下的不同存储实现基类都在namespace Storage下，
以上两个命名空间都是抽象类不可以被实例化，继承namespace Storage内的各种实现类才可以
例： 
(ADT::Liner_List 约束Logic::Liner_List ,static_assert(Logic::Liner_List)的接口规范)[c++20]
Logic::Liner_List   线性表(逻辑结构) 
↓
Storage::Sequential_List 顺序表(线性表的顺序存储) 
↓
Sequential_List_Static(顺序表的具体实现)

# 设计目标
- 重点是数据结构，而不是STL
STL使用了容器、迭代器、算法三个组件实现了容器和算法的隔离，这样是有代价的
1. 不清楚是否有运行时开销，听说都是编译期开销，而不是运行时
2. 所有的操作针对接口编程，参考Allocator的4个接口，还有很多的typedef或者using 如 valu_type、pointer、reference等
会导致代码量膨胀，是否值得待考虑
3. 该项目目的是为了学习，不是框架，不架构，重点在数据结构、基础算法本身，所以这两部分是独立的，即不考虑迭代器
4. 如果要兼容STL，需要做大量的改动，精力有限，所以不考虑
5. 原则上不使用stl容器实现自制的数据结构容器，但是算法可以用，如sort、成员函数的实现等


> 以下stl都指的是gcc的标准库实现
vector的实现中，size()的实现使用的是内部的_M_impl._M_finish - _M_impl._M_start来计算元素个数,就是老式迭代器(指针直接相减)
我用的是维护length成员变量，需要在增删元素时更新length值。
vector不论c++11,还是c++20，都是两倍当前大小扩充内存，只是20的逻辑更复杂

## 双端队列实现
静态：
1. 顺序的循环队列数组
动态：
1. 仿std::queue 这种类似索引存储，类似hash表


# 有关容器是否应该动态和静态各自实现一个
> 可以尝试一下如果用默认构造，那就是动态的。
如果构造时传入size，则会限制容器的大小，即静态的
因为默认构造时，容器通常都还没有申请内部的存储空间，所以可以利用一下。如Sequence_Stack的默认构造

