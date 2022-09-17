#pragma once
#include "Tree_Binary.h"

//动态创建二叉搜索树
BTree* BinaryTree_Search_Init();
//删除二叉搜索树
void BinaryTree_Search_Destroy();
//递增输出所有元素(中序遍历)
void BinaryTree_Order_Increase(TNode* tree);

//返回树的深度
int BinaryTree_Search_Depth(BTree* tree);

//查找节点  O(Logn)
TNode* BinaryTree_Search_LocateElement(BTree* tree, DataType data);

//增加二叉搜索节点data
void BinaryTree_Search_Insert(BTree* tree, DataType data);
void BinaryTree_Search_Insert_NonRecursive(BTree* tree, DataType data);

//删除二叉搜索节点data
void BinaryTree_Search_Delete(BTree* tree, TNode* node, DataType data);

//返回二叉搜索子树最大节点
TNode* BinaryTree_Search_Locate_Max(BTree* tree);


