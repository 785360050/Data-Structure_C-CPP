#pragma once

#include <type_traits>
#include <vector>

template <typename NodeType>
using BST_Key_Type = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<NodeType &>().key)>>;

template <typename TreeType>
auto *BST_Get_Root(TreeType &tree)
{
    if constexpr (requires { tree.Tree_GetRoot(); })
        return tree.Tree_GetRoot();
    else
        return tree.root;
}

template <typename NodeType>
void Collect_BST_InOrder(NodeType *node, std::vector<BST_Key_Type<NodeType>> &keys)
{
    if (!node)
        return;
    Collect_BST_InOrder(node->left, keys);
    keys.push_back(node->key);
    Collect_BST_InOrder(node->right, keys);
}

template <typename TreeType>
auto Collect_BST_InOrder(TreeType &tree)
{
    using NodeType = std::remove_pointer_t<decltype(BST_Get_Root(tree))>;
    std::vector<BST_Key_Type<NodeType>> keys;
    Collect_BST_InOrder(BST_Get_Root(tree), keys);
    return keys;
}

template <typename TreeType>
int BST_Get_Depth(TreeType &tree)
{
    auto *root = BST_Get_Root(tree);
    if constexpr (requires { tree.Get_Depth(root); })
        return tree.Get_Depth(root);
    else if constexpr (requires { TreeType::Get_Depth(root); })
        return TreeType::Get_Depth(root);
    else
    {
        BOOST_FAIL("Get_Depth(node) interface is not available on this Tree_Binary_Search implementation.");
        return 0;
    }
}

template <typename TreeType>
void Check_Tree_Binary_Search_Empty_Search_Behaviour()
{
    TreeType tree;

    BOOST_CHECK(BST_Get_Root(tree) == nullptr);
    BOOST_CHECK(tree.Node_Search(42) == nullptr);
}

template <typename TreeType>
void Check_Tree_Binary_Search_Insert_And_Search_Behaviour()
{
    TreeType tree;

    tree.Element_Insert(4, 40);
    tree.Element_Insert(2, 20);
    tree.Element_Insert(6, 60);
    tree.Element_Insert(1, 10);
    tree.Element_Insert(3, 30);
    tree.Element_Insert(5, 50);
    tree.Element_Insert(7, 70);

    BOOST_REQUIRE(tree.Node_Search(4) != nullptr);
    BOOST_REQUIRE(tree.Node_Search(1) != nullptr);
    BOOST_REQUIRE(tree.Node_Search(7) != nullptr);
    BOOST_CHECK(tree.Node_Search(99) == nullptr);
}

template <typename TreeType>
void Check_Tree_Binary_Search_Delete_Behaviour()
{
    TreeType tree;

    for (int key : {4, 2, 6, 1, 3, 5, 7})
        tree.Element_Insert(key, key * 10);

    tree.Element_Delete(2);
    BOOST_CHECK(tree.Node_Search(2) == nullptr);

    const std::vector<int> expected{1, 3, 4, 5, 6, 7};
    BOOST_CHECK(Collect_BST_InOrder(tree) == expected);
}

template <typename TreeType>
void Check_Tree_Binary_Search_InOrder_Sorted_Behaviour()
{
    TreeType tree;

    for (int key : {8, 3, 10, 1, 6, 14, 4, 7, 13})
        tree.Element_Insert(key, key);

    const std::vector<int> expected{1, 3, 4, 6, 7, 8, 10, 13, 14};
    BOOST_CHECK(Collect_BST_InOrder(tree) == expected);
}

template <typename TreeType>
void Check_Tree_Binary_Search_Depth_Interface_Is_Callable()
{
    TreeType tree;

    for (int key : {4, 2, 6, 1, 3})
        tree.Element_Insert(key, key);

    BOOST_CHECK_GE(BST_Get_Depth(tree), 1);
}

template <typename TreeType>
void Run_Tree_Binary_Search_Behaviour_Suite()
{
    Check_Tree_Binary_Search_Empty_Search_Behaviour<TreeType>();
    Check_Tree_Binary_Search_Insert_And_Search_Behaviour<TreeType>();
    Check_Tree_Binary_Search_Delete_Behaviour<TreeType>();
    Check_Tree_Binary_Search_InOrder_Sorted_Behaviour<TreeType>();
    Check_Tree_Binary_Search_Depth_Interface_Is_Callable<TreeType>();
}
