#pragma once

#if __cplusplus >= 202002L
#include <concepts>

namespace ADT
{
    template <typename StructureType, typename DataType, typename KeyType, typename NodeType>
    concept Tree_Binary_Search = requires(StructureType adt, DataType &&element, KeyType &&key, NodeType &&node) {
        // adt.Node_Next(node);
        // adt.Node_Precursor(node);
        adt.Element_Insert(key);
        adt.Element_Delete(key);
        adt.Node_Search(key);
    };
}

#endif

