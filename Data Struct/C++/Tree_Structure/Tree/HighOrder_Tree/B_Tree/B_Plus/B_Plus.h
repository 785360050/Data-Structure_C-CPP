#pragma once

#include <iostream>
#include <queue>

#include "Node_BPlus.h"

///————————————————————————————————————
/// 索引节点 和 叶子节点 使用不同的节点类型
/// 树根始终指向索引节点->即只有一个叶子节点的B+数也有一个索引节点
/// 索引节点的key存放下层节点的开头key(无第一个叶子的任何key)
///————————————————————————————————————

using KeyType = int;
using DataType = int;

//using Node = Node_BPlus<KeyType, DataType>;
template
<
    typename KeyType, typename DataType
//    typename NodeType_Index = Node_BPlus_Leaf<KeyType, DataType>,
//    typename NodeType_Leaf= Node_BPlus_Leaf<KeyType, DataType>
>
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
            for (auto each : node->index_ptr)
            {
                if (each)
                    Destroy(each);
            }
            delete node;
            //count--;
        }
    }
    ~Tree_BPlus()
    {
        //std::cout << "删除B树节点个数:" << count << std::endl;
        if (root)
        {
            for (auto each:root->index_ptr)
                Destroy(each);
        }
        delete root;
    }
private:
    //返回叶节点的父节点(叶节点？),并在叶节点中找key的下标，不存在时返回小值(找左孩子)
    std::pair<Node_BPlus<KeyType, DataType>*, int> keyIndexInLeaf(KeyType key)
    {
        /*
        *    @brief Find the location of given _key in leaf Node_BPlus<KeyType, DataType>.
        *    @param _key: Key we want to locate.
        *    @return A pair of leaf and index of given _key. If _key not in B+ tree, the index is the nearest and smaller key than given _key.
        */
        try
        {
            if (root == nullptr) ///树空时返回空
                throw std::exception("Root is not exsist");
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
                return std::make_pair(nullptr, 0);
        }

        Node_BPlus<KeyType, DataType>* node = root;
        while (true)
        {
            int loc = node->Index_Key(key);
            if (node->leaf)
                return std::make_pair(node, loc);
            else ///向下层节点找
                node = node->index_ptr[loc];
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

        int mid = leaf->key.size() / 2;

        ///移动后半部分元素到新节点
        new_leaf->key.assign(leaf->key.begin() + mid, leaf->key.end());
        leaf->key.erase(leaf->key.begin() + mid, leaf->key.end());
        new_leaf->data.assign(leaf->data.begin() + mid, leaf->data.end());
        leaf->data.erase(leaf->data.begin() + mid, leaf->data.end());

        return new_leaf;
    }
    //分割容量不足的索引节点，返回新索引节点
    std::pair<Node_BPlus<KeyType, DataType>*, DataType> IndexNode_Split(Node_BPlus<KeyType, DataType>* node)
    {
        Node_BPlus<KeyType, DataType>* new_node = new Node_BPlus<KeyType, DataType>(false);
        new_node->parent = node->parent;

        int mid = (node->key.size() + 1) / 2 - 1;
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
