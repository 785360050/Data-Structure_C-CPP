#pragma once

#include <math.h>
#include <sstream>
#include "../../List_Node.hpp"
#include <optional>
#include <vector>
#include <map>

#include "../Linear_List.hpp"


/// ============================================================================================================
/// 跳表
/// - 有序元素的链表，与二叉搜索树类似
/// - 跳表的增长由底层向上不断增高，与B树类似
/// - 元素节点的高度由随机几率决定
/// - 通常会限制最大层数，性能最佳。可以不限制，但是实现逻辑更复杂
///
/// 每个节点存一个element，节点指针有多级
///
/// 查找：O(logn)
/// 插入：定位O(logn) x 插入节点O(1) = O(logn)
/// 删除：定位O(logn) x 删除节点O(1) = O(logn)
///
/// 实现细节
/// - 支持动态扩展高度，使用vector作为头结点
/// - 由于搜索时申请释放的数组用于保存每层节点的前驱开销极大，
/// - 如果使用首元节点，则使用单链节点实现的逻辑简单
/// ============================================================================================================

namespace Storage
{

    // 实现参考 redis zset、《数据结构、算法与应用 C++语言描述 》10.4 跳表表示
    template <typename ElementType = int, float probable = 0.5f>
    class Skip_List : public Logic::Skip_List<ElementType>
    {
    public:
        using Node = List_Node_Skiplist<ElementType>;

    private:
        std::vector<Node *> header; // 头结点指针数组。支持层级扩展。header.size() == this->level   头结点的元素个数等于当前层数
        Node *tail;                 // 尾结点指针

        /// @brief
        /// 用于搜索目标节点时保存每层最后一个节点的搜索路径。
        /// search,insert,delete都需要用到
        ///
        /// 空间比当前level高一层因为可能新节点会使跳表的高度增加
        /// - 需要操作跳表时由_Loacte_Previous_Node()更新维护
        mutable std::map<size_t, Node *> search_path{};

    public:
        Skip_List()
        {
            static_assert(probable > 0 && probable < 1, "probable must be in (0, 1)");
            header.resize(32, {}); // 预留32层的头结点
        }
        ~Skip_List() override
        {
            // 删除所有结点和数组

            Node *node{header[0]};
            // 从headerNode开始，延数对链的方向删除
            while (node)
            {
                Node *node_delete = node;
                node = node->next[0];
                delete node_delete;
            }
        }

    private:
        // 随机一个元素所在的层级，用于计算实际的索引层数
        int _Determine_Level() const
        {
            // 获取一个表示链表级且不大于max_level的随机数
            static constexpr auto threshold = RAND_MAX * probable;
            int lev{}; // 0层作为最底层存放元素

            // lev限制在[0,level]中，防止lev远超过当前level过多，如当前skip_list3层，获取了一个60层的结果，则4-59层的链表都是空的
            // 使用while+随机计算lev可以控制每一层的节点的数量
            while (lev <= this->level && rand() <= threshold)
                ++lev;
            return lev; // 返回的结果∈[0,level+1] level+1表示向上增加一层
        }

        // 更新last_node_at_level： 搜索目标元素并把在每一级链表搜索时遇到的最后一个结点存储起来
        // 返回插入节点的前一个节点，可能等值
        void _Loacte_Previous_Node(const ElementType &element) const
        {
            search_path.clear(); // 清空上次操作的搜索路径

            // 从最高级链表开始查找，在每一级链表中，从左边尽可能逼近要查找的记录
            // 和Search逻辑比较类型，但是多了更新search_path的操作

            if (this->size == 0) // 跳表空时后续逻辑处理不了
            {
                search_path[0] = nullptr;
                return;
            }

            int level_start{static_cast<int>(this->level)};
            // 处理element小于最高节点的情况
            // 从第一个元素小于element的层开始向后遍历单链表
            while (level_start >= 0 && header[level_start]->element > element)
            {
                search_path[level_start] = nullptr;
                --level_start;
            }

            for (int i = level_start; i >= 0; --i)
            {
                Node *node = header[i];
                if (node->element == element) // 第一个节点就是目标节点
                {
                    search_path[i] = nullptr;
                    continue; // 不用return是因为要把下层的previous_node也更新到search_path中
                }
                // 定位到当层最接近的前驱节点。
                while (node->next[i] && node->next[i]->element < element)
                    node = node->next[i];
                // if (node->next[i] && node->next[i]->element == element)
                //     throw std::runtime_error("Key already exists");
                search_path[i] = node;
            }
        }

    public:
        // 搜索元素，
        // 返回所在的节点
        std::optional<ElementType> Element_Search(const ElementType &element) const override // O(logn)
        {
            // 从最高级链表开始查找，在每一级链表中，从左边尽可能逼近要查找的记录
            size_t level_start{this->level};
            // 处理element小于最高节点的情况
            // 从第一个元素小于element的层开始向后遍历单链表
            while (level_start != 0 && header[level_start]->element > element)
                --level_start;
            Node *node = header[level_start];

            for (int i = level_start; i >= 0; --i)
            {
                // 定位到当层最接近的节点。(小于目标的最大元素)
                while (node->next[i] && node->element < element)
                    node = node->next[i];
                if (node->element == element)
                    return node->element;
            }
            return std::nullopt;
        }

        // 插入元素
        void Element_Insert(const ElementType &element) override
        {

            // 查看和插入数对相同关键字的数对是否已经存在
            _Loacte_Previous_Node(element); // 定位到插入的节点位置
            if (!search_path.empty() && !search_path.contains(0) && search_path[0] != header[0] && search_path[0] != tail && search_path[0]->next[0]->element == element)
                throw std::runtime_error("Key already exists");

            // 如果不存在，则确定新结点所在的级链表
            int level_target = _Determine_Level(); // 新结点的级
            // 保证级theLevel <= levels + 1
            if (level_target > this->level) // 如果计算的层级结果大于当前的最大层级，则跳表增加一个层级
            {
                ++this->level; // 插入元素最多+1层，但是删除时可以一次减少多层
                // previous_node.push_back(header); // 添加了一层，则最顶层的前驱必定为header。用于后续的顶层节点插入
                if (header.size() < this->level + 1) // 头结点层数个数 < 需要的层数 ： size从1起始，level从0起始
                {
                    header.emplace_back(nullptr);
                    search_path[this->level] = nullptr;
                }
            }

            // 在结点theNode之后插入新结点
            Node *node = new Node(element, level_target);
            for (int i = 0; i <= level_target; ++i)
            {
                // 自下而上，插入i级链表
                if (i < search_path.size() && search_path.contains(i) && search_path[i] != nullptr)
                { // 当前层非空
                    node->next[i] = search_path[i]->next[i];
                    search_path[i]->next[i] = node;
                }
                else
                {
                    if (header.empty() || header.size() < i) // 在新层插入时先添加一个元素
                        header.emplace_back(nullptr);
                    node->next[i] = header[i]; // header[i]就是刚刚emplace_back(nullptr)
                    header[i] = node;
                }
            }
            if (!node->next[0])
                tail = node;

            ++this->size;
            return;
        }

        // 删除元素
        void Element_Delete(const ElementType &element) override
        {

            // 查看是否存在关键字匹配的数对
            _Loacte_Previous_Node(element);
            Node *previous_node = search_path[0];

            // Node *node_delete = search_path.contains(0) ? search_path[0]->next[0] : header[0];
            Node *node_delete = previous_node ? previous_node->next[0] : header[0];
            if (!node_delete || node_delete->element != element)
                // 不存在
                throw std::runtime_error("No such element " + std::to_string(element));
            // return;

            // 如果删除最高层级唯一的节点，则晚点降低一层跳表高度
            unsigned short decrease_level{};
            if (node_delete->level == this->level)
            {
                for (auto level = node_delete->level; level > 0; --level) // 最底层0层不用减
                {
                    if (header[level] == node_delete && node_delete->next[level] == nullptr)
                    {
                        ++decrease_level;
                        continue;
                    }
                    break;
                }
            }

            // 从跳表中删除结点
            for (int i = 0; i <= node_delete->level; ++i)
            {
                if (search_path[i] && search_path[i]->next[i] == node_delete)
                    search_path[i]->next[i] = node_delete->next[i];
                else
                    header[i] = node_delete->next[i];
            }

            if (node_delete->next[0] == nullptr) // 删除尾节点，更新tail
                tail = search_path[0];

            delete node_delete;
            --this->size;

            if (decrease_level && this->size) // size用于防止删除最后一个元素时，level减为-1
            {
                this->level -= decrease_level;
                // search_path.resize(level + 1);//缩容
            }
        }

    public:
        void List_Show(const std::string_view &info = "", bool only_elements = false)
        {

            if (only_elements)
            {
                // 遍历0级链表
                for (Node *node = header[0]; node; node = node->next[0])
                    std::cout << "[" << node->element << "] ";
                std::cout << "\tSize : " << this->size << std::endl;
            }
            else
            {
                std::cout << info << " ============= Level " << this->level << " =========== Size " << this->size << " =============== " << std::endl;
                for (size_t i{}; i <= this->level; ++i)
                {
                    size_t current_level{this->level - i}; // 从上到下遍历每一层
                    std::cout << "Level " << current_level << " : ";
                    for (Node *node = header[current_level]; node; node = node->next[current_level])
                        std::cout << "[" << node->element << "] ";
                    std::cout << std::endl;
                }
                std::cout << "============================================================= " << std::endl;
            }
        }
};
}

// 默认的实现方式
template <typename ElementType = int, float probable = 0.5f>
using Skip_List = Storage::Skip_List<ElementType, probable>;

#if __cplusplus >= 202002L
#include "../ADT.hpp"
static_assert(ADT::Skip_List<Skip_List<int, 0.5f>, int>);
#endif