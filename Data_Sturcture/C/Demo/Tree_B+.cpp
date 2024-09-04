
#include "../API/Tree_Advanced_B+_Tree.h"
#include <iostream>
int main()
{
    BPlus_Tree *tree = BPlus_Tree_Init(5);
    // for (int i = 0; i < 30; i++)
    for (int i = 0; i < 60; i++)
    {
        BPlus_Tree_Insert(tree, i, i);
        std::cout << std::endl;
        BPlus_Tree_Show(tree);
    }

    printf("\n删除元素\n");

    BPlus_Tree_Delete(tree, 37);
    BPlus_Tree_Show(tree);

    BPlus_Tree_Delete(tree, 1);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 2);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 3);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 4);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 5);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 6);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 7);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 8);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 9);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 10);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 11);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 12);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 26);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 25);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 23);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 22);
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 18); // 没有修改根节点数据
    BPlus_Tree_Show(tree);
    BPlus_Tree_Delete(tree, 21);
    BPlus_Tree_Show(tree);

    // for (int i = 1; i < 30; i += 2)
    //	BPlus_Tree_Insert(tree, i, i);
    // BPlus_Tree_Show(tree);

    // BPlus_Tree_Delete(tree, 0);
    // BPlus_Tree_Show(tree);
    // BPlus_Tree_Delete(tree, 9);
    // BPlus_Tree_Show(tree);
    // BPlus_Tree_Delete(tree, 17);
    // BPlus_Tree_Show(tree);
    // BPlus_Tree_Delete(tree, 21);
    // BPlus_Tree_Show(tree);

    for (int i = 0; i < 60; ++i)
        std::cout << "Key " << i << ':' << BPlus_Tree_Search(tree, i) << std::endl;

    BPlus_Tree_Destroy(tree);
}