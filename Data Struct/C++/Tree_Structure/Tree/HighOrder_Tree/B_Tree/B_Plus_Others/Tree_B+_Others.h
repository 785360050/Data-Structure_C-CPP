#pragma once

#include <iostream>
#include <vector>
#include <queue>


///————————————————————————————————
/// 默认B树节点元素个数最少为 1/2阶数(向下取值)
///		最多为 阶数-1
///————————————————————————————————

///参考代码
///https://github.com/yuesong-feng/BPlusTree

#define order 4
#define LEAF true

template<typename KeyT, typename ValT>
class Node 
{
public:
    bool leaf;      ///标记是否为叶节点
    Node* parent;   //for non-root only
    std::vector<KeyT> key;
    ///——————————
    /// non-leaf
    ///——————————
    std::vector<Node*> ptr2node;   
    ///——————————
    /// leaf
    ///——————————
    Node* next;     
    std::vector<ValT*> ptr2val;    
    
    Node(bool leaf = false)
        : leaf(leaf), parent(nullptr), next(nullptr) {}
};

template<typename KeyT, typename ValT>
class BPTree 
{
private:
    Node<KeyT, ValT>* root;
    
public:
    BPTree() : root(nullptr) {};

private:
    int keyIndex(Node<KeyT, ValT>* node, KeyT key)
    {///定位key在节点中的下标，不存在时返回小值(找左孩子)
        int loc = -1;
        while (node->key[loc + 1] <= key) 
        {
            loc++;
            if (loc == node->key.size() - 1) 
                break;///找不到返回末尾下标值
        }
        return loc;
    }
    //返回叶节点的父节点(叶节点？),并在叶节点中找key的下标，不存在时返回小值(找左孩子)
    std::pair<Node<KeyT, ValT>*, int> keyIndexInLeaf(KeyT key)
    {
        /*
        *    @brief Find the location of given _key in leaf node.
        *    @param _key: Key we want to locate.
        *    @return A pair of leaf and index of given _key. If _key not in B+ tree, the index is the nearest and smaller key than given _key.
        */
        if (root == nullptr) ///不存在根时新建根节点
            return std::make_pair(nullptr, static_cast<ValT>(0));
        Node<KeyT, ValT>* node = root;

        while (true) 
        {
            int loc = keyIndex(node, key);
            if (node->leaf) 
                return std::make_pair(node, loc);
            else ///向下层节点找
                node = node->ptr2node[loc + 1];
        }
    }
    //分割容量不足的叶节点，返回新叶节点
    Node<KeyT, ValT>* splitLeaf(Node<KeyT, ValT>* leaf)
    {
        Node<KeyT, ValT>* new_leaf = new Node<KeyT, ValT>(LEAF);
        new_leaf->next = leaf->next;
        leaf->next = new_leaf;
        new_leaf->parent = leaf->parent;
        int mid = leaf->key.size() / 2;

        ///移动后半部分元素到新节点
        new_leaf->key.assign(leaf->key.begin() + mid, leaf->key.end());
        leaf->key.erase(leaf->key.begin() + mid, leaf->key.end());
        new_leaf->ptr2val.assign(leaf->ptr2val.begin() + mid, leaf->ptr2val.end());
        leaf->ptr2val.erase(leaf->ptr2val.begin() + mid, leaf->ptr2val.end());
        
        return new_leaf;
    }
    //分割容量不足的索引节点，返回新索引节点
    std::pair<Node<KeyT, ValT>*, KeyT> splitNode(Node<KeyT, ValT>* node)
    {
        Node<KeyT, ValT>* new_node = new Node<KeyT, ValT>();
        new_node->parent = node->parent;
        int mid = (node->key.size() + 1) / 2 - 1;
        KeyT push_key = node->key[mid];     ///分割末尾节点元素提到上层

        ///移动后半部分元素到新节点
        new_node->key.assign(node->key.begin() + mid + 1, node->key.end());
        node->key.erase(node->key.begin() + mid, node->key.end());
        new_node->ptr2node.assign(node->ptr2node.begin() + mid + 1, node->ptr2node.end());
        node->ptr2node.erase(node->ptr2node.begin() + mid + 1, node->ptr2node.end());
        for (Node<KeyT, ValT>* each : new_node->ptr2node)
            each->parent = new_node;

        return std::make_pair(new_node, push_key);
    }
    void createIndex(Node<KeyT, ValT>* new_node, KeyT index)
    {
        /*
        *    @brief Create index for given new_node using index as index. The index will be inserted to new_node's parent.
        *    @param _new_node: Node we want to create index for.
        *    @param _index: Index of our new node. For leaf node, it should be the first key.
        *    @return void
        */
        Node<KeyT, ValT>* node = new_node->parent;
        int loc = keyIndex(node, index);
        node->key.insert(node->key.begin() + loc + 1, index);
        node->ptr2node.insert(node->ptr2node.begin() + loc + 2, new_node);
        if (node->key.size() > order) 
        {
            std::pair<Node<KeyT, ValT>*, KeyT> pair = splitNode(node);
            Node<KeyT, ValT>* new_node = pair.first;
            KeyT push_key = pair.second;
            if (node == root) {
                Node<KeyT, ValT>* new_root = new Node<KeyT, ValT>();
                new_root->key.push_back(push_key);
                new_root->ptr2node.push_back(node);
                new_root->ptr2node.push_back(new_node);
                root = new_root;
                node->parent = root;
                new_node->parent = root;
            }
            else {
                createIndex(new_node, push_key);
            }
        }
    }

public:
    void insert(KeyT key, ValT val)
    {
        if (root == nullptr) 
        {///树空时新建根节点
            root = new Node<KeyT, ValT>(LEAF);
            root->key.push_back(key);
            root->ptr2val.emplace_back(new ValT(val));
            root->ptr2node.push_back(nullptr);
            return;
        }
        std::pair<Node<KeyT, ValT>*, int> pair = keyIndexInLeaf(key);
        Node<KeyT, ValT>* leaf = pair.first;
        int loc = pair.second;
        if (loc != -1 && leaf->key[loc] == key) 
        {///K-V已存在
            std::cout << "Key " << key << " with value " << *(leaf->ptr2val[loc]) << " is already in B+ tree, overwrite it with new val " << val << std::endl;
            *(leaf->ptr2val[loc]) = val;
            return;
        }
        leaf->key.insert(leaf->key.begin() + loc + 1, key);
        leaf->ptr2val.insert(leaf->ptr2val.begin() + loc + 1, new ValT(val));
        if (leaf->key.size() > order) 
        {
            Node<KeyT, ValT>* new_leaf = splitLeaf(leaf);
            if (leaf == root) 
            {
                Node<KeyT, ValT>* new_root = new Node<KeyT, ValT>();
                new_root->key.push_back(new_leaf->key[0]);
                new_root->ptr2node.push_back(leaf);
                new_root->ptr2node.push_back(new_leaf);
                root = new_root;
                leaf->parent = root;
                new_leaf->parent = root;
            }
            else 
                createIndex(new_leaf, new_leaf->key[0]);
        }
    }
    void erase(KeyT _key)
    {
        /*
        *    @brief Delete _key from B+ tree
        *    @param _key: Key we want to delete
        *    @return void
        */
        std::pair<Node<KeyT, ValT>*, int> pair = keyIndexInLeaf(_key);
        Node<KeyT, ValT>* leaf = pair.first;
        int loc = pair.second;
        if (loc == -1 || leaf->key[loc] != _key) {
            std::cout << "Key " << _key << " is not in B+ tree" << std::endl;
            return;
        }

    }

    ValT* find(KeyT _key)
    {
        /*
        *    @brief Find the value ptr of given key in B+ tree
        *    @param _key: Key we want to find
        *    @return A ptr to value. If key is not in B+ tree then return nullptr
        */
        std::pair<Node<KeyT, ValT>*, int> pair = keyIndexInLeaf(_key);
        Node<KeyT, ValT>* leaf = pair.first;
        int loc = pair.second;
        if (loc == -1 || leaf->key[loc] != _key) {
            std::cout << "Key " << _key << " is not in B+ tree" << std::endl;
            return nullptr;
        }
        else {
            return leaf->ptr2val[loc];
        }

    }
    void display()
    {///层次遍历
        if (root == nullptr) 
        {
            std::cout << "B+ tree is empty!" << std::endl;
            return;
        }
        std::queue<Node<KeyT, ValT>*> q;
        q.push(root);
        while (!q.empty()) 
        {
            int q_size = q.size();
            while (q_size--) 
            {
                Node<KeyT, ValT>* node = q.front();
                q.pop();
                int key_size = node->key.size();
                if (node->leaf) 
                {
                    for (auto each : node->ptr2val)
                        std::cout << *each << " ";
                }
                else 
                {
                    for (auto each : node->key)
                        std::cout << each << " ";
                    for (auto each : node->ptr2node)
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
        Node<KeyT, ValT>* node = root;
        while (!node->leaf) {
            node = node->ptr2node[0];
        }
        while (node != nullptr) {
            for (auto each : node->ptr2val)
                std::cout << *each << " ";
            node = node->next;
        }
        std::cout << std::endl;
    }
};

