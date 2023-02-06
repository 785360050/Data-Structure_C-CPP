#pragma once

#include <vector>


template<typename KeyType, typename DataType>
class Tree_BPlus;

template<typename KeyType,typename DataType>
class Node_BPlus
{/// 使用一个结构同时表示叶子和节点，leaf区分索引节点和叶子节点
private:
    friend class Tree_BPlus<KeyType,DataType>;
protected:
    bool leaf;      ///标记是否为叶节点
    Node_BPlus* parent;  
    std::vector<KeyType> key;
    //int order;      ///阶数
protected:/// non-leaf
    std::vector<Node_BPlus*> index_ptr;      ///指针索引
protected:/// leaf
    Node_BPlus* next;
    std::vector<DataType> data;         ///数据数组

public:
    Node_BPlus(bool leaf = false)
        :leaf(leaf), parent(nullptr), next(nullptr) {};
public:
    //定位key在节点中的下标，不存在时返回size值
    int Index_Key(KeyType key)
    {
        int i = 0;
        for (i; i < this->key.size() && this->key[i] < key; ++i);
        return i;

        //int loc = 0;
        //while (this->key[loc] <= key)
        //{
        //    loc++;
        //    if (loc == this->key.size() - 1)
        //        break;///找不到返回末尾下标值
        //}
        //return loc;
    }
};





