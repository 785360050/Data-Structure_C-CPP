#pragma once

namespace ADT
{
    template <typename NodeType>
    concept Binary_Node = requires(NodeType *node) {
        node->left;
        node->right;
        // 左右孩子都是 NodeType* 类型
        // { node->left } -> std::same_as<NodeType *>;
        // { node->right } -> std::same_as<NodeType*>;
    };
}
