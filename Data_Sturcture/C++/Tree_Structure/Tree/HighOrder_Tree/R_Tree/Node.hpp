#pragma once

/// Minimal bounding rectangle (n-dimensional)
template <typename ElementType,int dim>
struct _Rect
{
    ElementType m_min[dim]{};  ///< Min dimensions of bounding box
    ElementType m_max[dim]{};  ///< Max dimensions of bounding box
};

// forword declare
template <typename DataType, typename ElementType, int dim, int maxnodes>
struct _Node;

/// May be data or may be another subtree
/// The parents level determines this.
/// If the parents level is 0, then this is data
template <typename DataType, typename ElementType, int dim, int maxnodes>
struct _Branch
{
    _Rect<ElementType, dim> m_rect; ///< Bounds
    union
    {
        _Node<DataType, ElementType, dim, maxnodes> *m_child; ///< Child node
        DataType m_data;         ///< Data Id or Ptr
    };
};

/// _Node for each branch level
// template <int maxnodes>
template <typename DataType, typename ElementType, int dim, int maxnodes>
struct _Node
{
    int m_count{};               ///< Count
    int m_level{-1};           ///< Leaf is zero, others positive
    _Branch<DataType, ElementType, dim, maxnodes> m_branch[maxnodes]; ///< Branch
public:
    bool Is_Branch() { return (m_level > 0); } // Not a leaf, but a internal node
    // bool IsLeaf() { return (m_level == 0); }        // A leaf, contains data
    
    void Reset()
    {
        m_count = 0;
        m_level = -1;
    }

    static _Node *AllocNode()
    {
        _Node *newNode = new _Node;
        newNode->Reset();
        return newNode;
    }
    void FreeNode()
    {
        ASSERT(this);
        // delete a_node;
        delete this;
    }
};



/// A link list of nodes for reinsertion after a delete operation
template <typename DataType, typename ElementType, int dim, int maxnodes>
struct _ListNode
{
    _ListNode *m_next{}; ///< Next in list
    _Node<DataType, ElementType, dim, maxnodes> *m_node{}; ///< _Node

    static _ListNode *Alloc()
    {
        // Allocate space for a node in the list used in DeletRect tostore Nodes that are too empty.
        return new _ListNode;
    }
};