#pragma once

#include <iostream>
#include <queue>

#include "Node_BPlus.hpp"

///————————————————————————————————————
/// 索引节点 和 叶子节点 使用不同的节点类型
/// 树根始终指向索引节点->即只有一个叶子节点的B+数也有一个索引节点
/// 索引节点的key存放下层节点的开头key(无第一个叶子的任何key)
///————————————————————————————————————

using KeyType = int;
using DataType = int;

template<typename KeyType, typename DataType>
class Tree_BPlus
{
private:
    Node_BPlus<KeyType, DataType>* root;
    int order;      ///树的度

public:
    Tree_BPlus(int order, Node_BPlus<KeyType, DataType>* root = nullptr)
        :order(order), root(root) {};
    void Destroy(Node_BPlus<KeyType, DataType>* node)
    {
        if (node)
        {
            for(int i=0;i<node->length_index;++i)
            {
                if (node->index_ptr[i])
                    Destroy(node->index_ptr[i]);
            }
            delete node;
        }
    }
    ~Tree_BPlus()
    {
        //std::cout << "删除B树节点个数:" << count << std::endl;
        if (root)
        {
            for (int i = 0; i < root->length_index; ++i)
                Destroy(root->length_index[i]);
        }
        delete root;
    }
private:
    //返回叶节点的父节点(叶节点？),并在叶节点中找key的下标，不存在时返回小值(找左孩子)
    std::pair<Node_BPlus<KeyType, DataType>*, int> Index_Key_Leaf(KeyType key)
    {
        try
        {
            if (root == nullptr) ///树空时返回空
                throw std::runtime_error("Root is not exsist");
        }
        catch (const std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
            return std::make_pair(nullptr, 0);
        }

        Node_BPlus<KeyType, DataType>* node = root;
        while (true)
        {
            int loc = node->Index_Key(key);
            if (!node->leaf) ///非叶节点向下层找
                node = node->index_ptr[loc];
            else ///此时为叶节点
                return std::make_pair(node, loc);
        }
    }
    //分割容量不足的叶节点，返回新叶节点
    Node_BPlus<KeyType, DataType>* Leaf_Split(Node_BPlus<KeyType, DataType>* leaf)
    {
        Node_BPlus<KeyType, DataType>* new_leaf = new Node_BPlus<KeyType, DataType>(true);

        ///插入新链节点
        new_leaf->next = leaf->next;
        leaf->next = new_leaf;
        new_leaf->parent = leaf->parent;

        int mid = leaf->length_data / 2;

        for (int i = mid, j = 0; i <= order; ++i)
        {///移动后半部分元素到新节点
            new_leaf->key[j] = leaf->key[i];
            leaf->key[i] = NULL;
            new_leaf->data[j] = leaf->data[j];
            leaf->data[j] = NULL;
        }

        //new_leaf->key.assign(leaf->key.begin() + mid, leaf->key.end());
        //leaf->key.erase(leaf->key.begin() + mid, leaf->key.end());
        //new_leaf->data.assign(leaf->data.begin() + mid, leaf->data.end());
        //leaf->data.erase(leaf->data.begin() + mid, leaf->data.end());

        return new_leaf;
    }
    //分割容量不足的索引节点，返回新索引节点
    std::pair<Node_BPlus<KeyType, DataType>*, DataType> IndexNode_Split(Node_BPlus<KeyType, DataType>* node)
    {
        Node_BPlus<KeyType, DataType>* new_node = new Node_BPlus<KeyType, DataType>(false);
        new_node->parent = node->parent;

        int mid = (node->length_index) / 2;
        KeyType push_key = node->key[mid];     ///分割末尾节点元素提到上层

        ///移动后半部分元素到新节点
        new_node->key.assign(node->key.begin() + mid + 1, node->key.end());
        node->key.erase(node->key.begin() + mid, node->key.end());
        new_node->index_ptr.assign(node->index_ptr.begin() + mid + 1, node->index_ptr.end());
        node->index_ptr.erase(node->index_ptr.begin() + mid + 1, node->index_ptr.end());
        for (auto each : new_node->index_ptr)
            each->parent = new_node;    ///转移下层节点的父节点

        return std::make_pair(new_node, push_key);
    }
    void IndexNode_create(Node_BPlus<KeyType, DataType>* new_node, DataType index)
    {
        /*
        *    @brief Create index for given new_node using index as index. The index will be inserted to new_node's parent.
        *    @param _new_node: Node we want to create index for.
        *    @param _index: Index of our new node. For leaf node, it should be the first key.
        *    @return void
        */
        Node_BPlus<KeyType, DataType>* node = new_node->parent;
        int loc = node->Index_Key(index);
        node->key.insert(node->key.begin() + loc, index);
        node->index_ptr.insert(node->index_ptr.begin() + loc + 1, new_node);
        if (node->key.size() > order)
        {
            std::pair<Node_BPlus<KeyType, DataType>*, KeyType> pair = IndexNode_Split(node);
            Node_BPlus<KeyType, DataType>* new_node = pair.first;
            KeyType push_key = pair.second;
            if (node == root) 
            {
                Node_BPlus<KeyType, DataType>* new_root = new Node_BPlus<KeyType, DataType>(false);
                new_root->key.push_back(push_key);
                new_root->index_ptr.push_back(node);
                new_root->index_ptr.push_back(new_node);
                root = new_root;
                node->parent = root;
                new_node->parent = root;
            }
            else 
                IndexNode_create(new_node, push_key);
        }
    }

public:
    void insert(KeyType key, DataType data)
    {
        if (root == nullptr)
        {///树空时新建根节点
            root = new Node_BPlus<KeyType, DataType>(true);
            root->key.push_back(key);
            root->data.emplace_back(data);
            root->index_ptr.push_back(nullptr);
        }
        else
        {///非空树
            std::pair<Node_BPlus<KeyType, DataType>*, int> pair = keyIndexInLeaf(key);
            Node_BPlus<KeyType, DataType>* leaf = pair.first;
            int loc = pair.second;
            if (loc != leaf->key.size() && leaf->key[loc] == key)
            {///K-V已存在
                std::cout << "Key " << key << " with value " << leaf->data[loc] << " is already in B+ tree, overwrite it with new val " << data << std::endl;
                //leaf->data[loc] = data;
                return;
            }
            else
            {///K-V不存在时
                leaf->key.insert(leaf->key.begin() + loc, key);
                leaf->data.insert(leaf->data.begin() + loc, data);
                if (leaf->key.size() > order)
                {///超出容量时分割
                    Node_BPlus<KeyType, DataType>* new_leaf = Leaf_Split(leaf);
                    if (leaf == root)
                    {///新建根节点
                        Node_BPlus<KeyType, DataType>* new_root = new Node_BPlus<KeyType, DataType>(false);
                        root = new_root;
                        new_root->key.push_back(leaf->key[leaf->key.size() - 1]);   ///原叶节点的末尾元素向上提
                        new_root->index_ptr.push_back(leaf);
                        new_root->index_ptr.push_back(new_leaf);
                        leaf->parent = new_leaf->parent = root;
                    }
                    else
                        IndexNode_create(new_leaf, leaf->key[leaf->key.size() - 1]);    ///原叶节点的末尾元素向上提
                }
            }
        }
    }


    void RestoreBTree(Node_BPlus<KeyType, DataType>* node)
    {
        ///父节点不存在，即无需调整根节点(B+树只有唯一一个节点，且为根节点)
        if (!node->parent)
            return;

        Node_BPlus<KeyType, DataType>* parent, * brother_left, * brother_right;
        {///初始化 brothers,parent
            parent = node->parent;

            int i_index;	///指向调整节点的索引指针
            for (i_index = 0; i_index < parent->index_ptr.size(); ++i_index)
            {///遍历父节点中的索引指针,以找到左右兄弟节点
                if (parent->index_ptr[i_index] == node)
                    break;
            }///parent->index_ptr[i_index] 指向当前节点
            brother_left = parent->index_ptr[i_index];
            brother_right = parent->index_ptr[i_index + 1];
        }

        if (brother_left && brother_left->key.size() > order / 2)
        {///左兄弟有多余元素，则从左兄弟借元素
            /// 从左兄弟借元素 = 从父节点借小元素(逻辑前驱) + 父节点从左节点借最大的元素(逻辑前驱)

            ///移动左叶兄弟的末尾元素到当前节点
            node->key.insert(node->key.begin(), brother_left->key[brother_left->key.size() - 1]);
            node->data.insert(node->data.begin(), brother_left->data[brother_left->data.size() - 1]);
            brother_left->key.erase(brother_left->key.end() - 1);
            brother_left->data.erase(brother_left->data.end() - 1);

            ///更新父节点key为左兄的末尾元素
            brother_left->parent->key[brother_left->parent->key.size() - 1] = brother_left->key[brother_left->key.size() - 1];
        }
        else if (brother_right && brother_right->key.size() > order / 2)
        {///右兄弟有多余元素，则从右兄弟借
            ///从右兄弟借元素 = 从父节点借大元素(逻辑后继) + 父节点从右兄弟借最小元素(逻辑后继)
            ///移动右叶兄弟的首元素
            node->key.insert(node->key.end() - 1, brother_right->key[0]);
            node->data.insert(node->data.end(), brother_right->data[0]);
            brother_right->key.erase(brother_right->key.begin());
            brother_right->data.erase(brother_right->data.begin());

            ///更新父节点
            node->parent->key[brother_left->parent->key.size() - 1] = node->key[node->key.size() - 1];
        }
        else
        {///左右兄弟都无法借元素，只能合并
            if (brother_left)
            {///调整节点与左兄弟合并
                ///合并 = 从父节点移动分割元素到左兄弟 + 当前节点元素都移到左节点 

                for (int i = 0; i < node->key.size(); ++i)
                {///移动所有元素给左叶兄弟
                    brother_left->key.push_back(node->key[i]);
                    brother_left->data.push_back(node->data[i]);
                }

                for (int index = 0; index < parent->index_ptr.size(); ++index)
                {///更新索引节点的索引指针
                    if (parent->index_ptr[index] == node)
                    {
                        parent->index_ptr.erase(parent->index_ptr.begin() + index);
                        break;
                    }
                }
                delete node;

                //
                if (root == parent)
                {/// 如果此时父节点为根，则当父节点没有关键字时才调整
                    if (parent->key.empty())
                    {
                        root = node;
                        delete node->parent;
                    }
                }
                else
                {/// 如果父节点不为根，则需要判断是否需要重新调整
                    if (parent->key.size() < order / 2)
                        RestoreBTree(parent);
                }

            }
            else if (brother_right)
            {///调整节点与右兄弟合并
                ///合并 = 从父节点移动分割元素(逻辑后继)到左兄弟 + 右兄弟元素都移到调整节点 

                for (int i = 0; i < brother_right->key.size(); ++i)
                {///移动所有元素给当前兄弟
                    node->key.push_back(node->key[i]);
                    node->data.push_back(node->data[i]);
                }

                for (int index = 0; index < parent->index_ptr.size(); ++index)
                {///更新索引节点的索引指针
                    if (parent->index_ptr[index] == brother_right)
                    {
                        parent->index_ptr.erase(parent->index_ptr.begin() + index);
                        break;
                    }
                }
                delete brother_right;


                if (root == parent)
                {/// 如果此时父节点为根，则当父节点没有关键字时才调整
                    if (parent->key.empty())
                    {
                        root = node;
                        delete node->parent;
                    }
                }
                else
                {/// 如果父节点不为根，则需要判断是否需要重新调整
                    if (parent->key.size() < order / 2)
                        RestoreBTree(parent);
                }
            }
            else
            {
                std::cout << "Error: 左右兄弟都不存在";
            }
        }
    }
    
    void Delete(Node_BPlus<KeyType, DataType>* node, int position)
    {///删除node节点中下标为Position的元素
        node->key.erase(node->key.begin() + position);
        node->data.erase(node->data.begin() + position);

        if (node->key.size() < order / 2)	///阈值可自定义
            RestoreBTree(node);///调整B树

        if (position == node->key.size())
        {///删除末尾元素时，更新上层索引节点key
            //Update_Index();
            for (int i = 0; i < node->parent->key.size(); ++i)
            {
                if (node->parent->index_ptr[i] == node)
                    node->parent->key[i] = node->key[node->key.size() - 1];
            }
        }

    }

    void erase(KeyType _key)
    {
        std::pair<Node_BPlus<KeyType, DataType>*, int> pair = keyIndexInLeaf(_key);
        Node_BPlus<KeyType, DataType>* leaf = pair.first;
        int loc = pair.second;
        if (loc == leaf->key.size() || leaf->key[loc] != _key)
        {
            std::cout << "Key " << _key << " is not in B+ tree" << std::endl;
            return;
        }

        Delete(leaf, loc);
        //--count;
        

    }

    DataType find(KeyType _key)
    {
        /*
        *    @brief Find the value ptr of given key in B+ tree
        *    @param _key: Key we want to find
        *    @return A ptr to value. If key is not in B+ tree then return nullptr
        */
        std::pair<Node_BPlus<KeyType, DataType>*, int> pair = keyIndexInLeaf(_key);
        Node_BPlus<KeyType, DataType>* leaf = pair.first;
        int loc = pair.second;
        if (loc == leaf->key.size() || leaf->key[loc] != _key)
        {
            std::cout << "Key " << _key << " is not in B+ tree" << std::endl;
            return NULL;
        }
        else 
            return leaf->data[loc];
    }
    void display()
    {///层次遍历
        if (root == nullptr)
        {
            std::cout << "B+ tree is empty!" << std::endl;
            return;
        }
        std::queue<Node_BPlus<KeyType, DataType>*> q;
        q.push(root);
        while (!q.empty())
        {
            int q_size = q.size();
            while (q_size--)
            {
                Node_BPlus<KeyType, DataType>* node = q.front();
                q.pop();
                int key_size = node->key.size();
                if (node->leaf)
                {///输出索引节点
                    for (auto each : node->key)
                        std::cout << each << " ";
                }
                else
                {///输出叶节点
                    for (auto each : node->key)
                        std::cout << each << " ";
                    for (auto each : node->index_ptr)
                        q.push(each);
                }
                std::cout << "| ";
            }
            std::cout << std::endl;
        }
    }
    void scan()
    {
        if (root == nullptr) {
            std::cout << "B+ tree is empty!" << std::endl;
            return;
        }
        Node_BPlus<KeyType, DataType>* node = root;
        while (!node->leaf) {
            node = node->index_ptr[0];
        }
        while (node != nullptr) {
            for (auto each : node->index_ptr)
                std::cout << each << " ";
            node = node->next;
        }
        std::cout << std::endl;
    }
};
