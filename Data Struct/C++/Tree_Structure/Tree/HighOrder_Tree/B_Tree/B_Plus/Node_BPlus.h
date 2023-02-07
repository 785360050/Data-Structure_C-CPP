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
    KeyType* key;
    int length_key; ///key数组当前元素个数
protected:/// non-leaf
    Node_BPlus* index_ptr;      ///索引指针
    int length_index;   ///当前索引指针个数
protected:/// leaf
    Node_BPlus* next;
    DataType data;         ///数据数组
    int length_data;    ///数据个数

public:
    Node_BPlus(bool leaf = false)
        :leaf(leaf), parent(nullptr), next(nullptr),
        length_key(0),length_index(0),length_data(0)
    {};
public:
    //定位key在节点中的下标，不存在时返回maxsize值
    int Index_Key(KeyType key)
    {
        int i = 0;
        for (i; i < this->length_key && this->key[i] < key; ++i);
        return i;
    }
    bool Index_Validity(int position)
    {

    }
};





