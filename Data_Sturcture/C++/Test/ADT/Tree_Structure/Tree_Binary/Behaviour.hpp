#pragma once

#include <queue>
#include <string>
#include <vector>

template <typename NodeType>
void Collect_Tree_Binary_PreOrder(NodeType *node, std::vector<std::string> &order)
{
    if (!node)
        return;
    order.push_back(node->name);
    Collect_Tree_Binary_PreOrder(node->left, order);
    Collect_Tree_Binary_PreOrder(node->right, order);
}

template <typename NodeType>
void Collect_Tree_Binary_InOrder(NodeType *node, std::vector<std::string> &order)
{
    if (!node)
        return;
    Collect_Tree_Binary_InOrder(node->left, order);
    order.push_back(node->name);
    Collect_Tree_Binary_InOrder(node->right, order);
}

template <typename NodeType>
void Collect_Tree_Binary_PostOrder(NodeType *node, std::vector<std::string> &order)
{
    if (!node)
        return;
    Collect_Tree_Binary_PostOrder(node->left, order);
    Collect_Tree_Binary_PostOrder(node->right, order);
    order.push_back(node->name);
}

template <typename NodeType>
std::vector<std::string> Collect_Tree_Binary_LevelOrder(NodeType *node)
{
    std::vector<std::string> order;
    if (!node)
        return order;

    std::queue<NodeType *> queue;
    queue.push(node);
    while (!queue.empty())
    {
        NodeType *current = queue.front();
        queue.pop();
        order.push_back(current->name);
        if (current->left)
            queue.push(current->left);
        if (current->right)
            queue.push(current->right);
    }
    return order;
}

template <typename TreeType>
void Check_Tree_Binary_Root_And_Insert_Behaviour()
{
    TreeType tree;

    BOOST_CHECK(tree.Tree_CheckEmpty());
    BOOST_CHECK(tree.Tree_GetRoot() == nullptr);

    auto *root = tree.Node_Create("A", 1);
    auto *left_child = tree.Node_Create("B", 2);
    auto *right_child = tree.Node_Create("C", 3);

    tree.Tree_Set_Root(root);
    tree.Node_Insert(left_child, root, static_cast<Direction>(1));
    tree.Node_Insert(right_child, root, static_cast<Direction>(2));

    BOOST_CHECK(!tree.Tree_CheckEmpty());
    BOOST_REQUIRE(tree.Tree_GetRoot() != nullptr);
    BOOST_CHECK_EQUAL(tree.Tree_GetRoot()->name, "A");
    BOOST_REQUIRE(tree.Tree_GetRoot()->left != nullptr);
    BOOST_REQUIRE(tree.Tree_GetRoot()->right != nullptr);
    BOOST_CHECK_EQUAL(tree.Tree_GetRoot()->left->name, "B");
    BOOST_CHECK_EQUAL(tree.Tree_GetRoot()->right->name, "C");
}

template <typename TreeType>
void Check_Tree_Binary_Traverse_Interfaces_Are_Executable()
{
    TreeType tree;

    auto *root = tree.Node_Create("A", 1);
    auto *left_child = tree.Node_Create("B", 2);
    auto *right_child = tree.Node_Create("C", 3);
    auto *left_left = tree.Node_Create("D", 4);

    tree.Tree_Set_Root(root);
    tree.Node_Insert(left_child, root, static_cast<Direction>(1));
    tree.Node_Insert(right_child, root, static_cast<Direction>(2));
    tree.Node_Insert(left_left, left_child, static_cast<Direction>(1));

    const std::vector<std::string> expected_pre{"A", "B", "D", "C"};
    const std::vector<std::string> expected_in{"D", "B", "A", "C"};
    const std::vector<std::string> expected_post{"D", "B", "C", "A"};
    const std::vector<std::string> expected_level{"A", "B", "C", "D"};

    std::vector<std::string> actual_pre;
    std::vector<std::string> actual_in;
    std::vector<std::string> actual_post;

    Collect_Tree_Binary_PreOrder(tree.Tree_GetRoot(), actual_pre);
    Collect_Tree_Binary_InOrder(tree.Tree_GetRoot(), actual_in);
    Collect_Tree_Binary_PostOrder(tree.Tree_GetRoot(), actual_post);

    BOOST_CHECK(actual_pre == expected_pre);
    BOOST_CHECK(actual_in == expected_in);
    BOOST_CHECK(actual_post == expected_post);
    BOOST_CHECK(Collect_Tree_Binary_LevelOrder(tree.Tree_GetRoot()) == expected_level);

    BOOST_CHECK_NO_THROW(tree.Tree_Traverse_PreOrder(tree.Tree_GetRoot()));
    BOOST_CHECK_NO_THROW(tree.Tree_Traverse_InOrder(tree.Tree_GetRoot()));
    BOOST_CHECK_NO_THROW(tree.Tree_Traverse_PostOrder(tree.Tree_GetRoot()));
    BOOST_CHECK_NO_THROW(tree.Tree_Traverse_LevelOrder(tree.Tree_GetRoot()));
}

template <typename TreeType>
void Check_Tree_Binary_Build_Is_Executable()
{
    TreeType preorder_tree;

    preorder_tree.Tree_Build({1, 2, 3}, {2, 1, 3}, true);
    BOOST_REQUIRE(preorder_tree.Tree_GetRoot() != nullptr);
    BOOST_CHECK_EQUAL(preorder_tree.Tree_GetRoot()->name, "1");
    BOOST_REQUIRE(preorder_tree.Tree_GetRoot()->left != nullptr);
    BOOST_REQUIRE(preorder_tree.Tree_GetRoot()->right != nullptr);
    BOOST_CHECK_EQUAL(preorder_tree.Tree_GetRoot()->left->name, "2");
    BOOST_CHECK_EQUAL(preorder_tree.Tree_GetRoot()->right->name, "3");

    TreeType postorder_tree;
    postorder_tree.Tree_Build({2, 3, 1}, {2, 1, 3}, false);
    BOOST_REQUIRE(postorder_tree.Tree_GetRoot() != nullptr);
    BOOST_CHECK_EQUAL(postorder_tree.Tree_GetRoot()->name, "1");
    BOOST_REQUIRE(postorder_tree.Tree_GetRoot()->left != nullptr);
    BOOST_REQUIRE(postorder_tree.Tree_GetRoot()->right != nullptr);
    BOOST_CHECK_EQUAL(postorder_tree.Tree_GetRoot()->left->name, "2");
    BOOST_CHECK_EQUAL(postorder_tree.Tree_GetRoot()->right->name, "3");
}

template <typename TreeType>
void Run_Tree_Binary_Behaviour_Suite()
{
    Check_Tree_Binary_Root_And_Insert_Behaviour<TreeType>();
    Check_Tree_Binary_Traverse_Interfaces_Are_Executable<TreeType>();
    Check_Tree_Binary_Build_Is_Executable<TreeType>();
}
